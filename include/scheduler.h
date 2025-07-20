#pragma once
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include "task.h"

class Scheduler {
public:
    Scheduler(int num_threads = 4);
    ~Scheduler();

    void start();
    void stop();
    void addTask(int id, int priority, int exec_time);
    void printStatus();

private:
    std::priority_queue<Task> taskQueue;
    std::vector<std::thread> workers;
    std::unordered_map<int, std::string> workerStatus;
    std::mutex queueMutex;
    std::condition_variable cv;
    std::thread agingThread;

    bool running;

    void startAging();
    void stopAging();
    void agingLoop();
    void workerThreadLoop(int id);
};
