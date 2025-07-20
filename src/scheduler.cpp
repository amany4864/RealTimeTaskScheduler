#include "scheduler.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <queue>
#include <algorithm>

Scheduler::Scheduler(int num_threads) : running(false) {
    workers.reserve(num_threads);
}

Scheduler::~Scheduler() {
    stop();
}

void Scheduler::startAging() {
    agingThread = std::thread(&Scheduler::agingLoop, this);
}

void Scheduler::stopAging() {
    if (agingThread.joinable()) {
        agingThread.join();
    }
}

void Scheduler::agingLoop() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Every second

        std::lock_guard<std::mutex> lock(queueMutex);
        std::vector<Task> temp;

        while (!taskQueue.empty()) {
            Task t = taskQueue.top();
            taskQueue.pop();
            t.waiting_time += 1000;

            if (t.waiting_time >= 3000 && t.priority > 0) {
                t.priority -= 1;
                t.waiting_time = 0;
                std::cout << "[Aging] Boosted Task " << t.id << " to priority " << t.priority << std::endl;
            }

            temp.push_back(t);
        }

        for (Task& t : temp) {
            taskQueue.push(t);
        }

        cv.notify_all();
    }
}

void Scheduler::start() {
    running = true;
    startAging();

    int num_threads = 4;
    for (int i = 0; i < num_threads; ++i) {
        workers.emplace_back(&Scheduler::workerThreadLoop, this, i);
    }
}

void Scheduler::stop() {
    running = false;
    stopAging();
    cv.notify_all();

    for (auto& t : workers) {
        if (t.joinable()) t.join();
    }
}

void Scheduler::addTask(int id, int priority, int exec_time) {
    std::lock_guard<std::mutex> lock(queueMutex);
    taskQueue.emplace(id, priority, exec_time);
    cv.notify_one();
}

void Scheduler::printStatus() {
    std::lock_guard<std::mutex> lock(queueMutex);

    std::cout << "\n--- Scheduler Status ---" << std::endl;
    std::cout << "Pending Tasks: " << taskQueue.size() << std::endl;

    std::priority_queue<Task> copy = taskQueue;
    std::vector<Task> pending;
    while (!copy.empty()) {
        pending.push_back(copy.top());
        copy.pop();
    }

    std::sort(pending.begin(), pending.end(), [](const Task& a, const Task& b) {
        return a.priority > b.priority;
    });

    for (const auto& task : pending) {
        std::cout << "Task ID: " << task.id
                  << " | Priority: " << task.priority
                  << " | Exec: " << task.execution_time << "ms"
                  << " | Waited: " << task.waiting_time << "ms" << std::endl;
    }

    std::cout << "\nWorker Status:\n";
    for (auto& pair : workerStatus) {
        std::cout << "Worker " << pair.first << ": " << pair.second << std::endl;
    }

    std::cout << "-------------------------\n" << std::endl;
}

void Scheduler::workerThreadLoop(int id) {
    while (running) {
        Task task(0, 0, 0);
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            cv.wait(lock, [&] { return !taskQueue.empty() || !running; });

            if (!running && taskQueue.empty()) return;

            task = taskQueue.top();
            taskQueue.pop();
            workerStatus[id] = "Running Task " + std::to_string(task.id);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(task.execution_time));

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            workerStatus[id] = "Idle";
        }

        std::cout << "Task " << task.id << " completed by Worker " << id << std::endl;
    }
}
