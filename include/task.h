#ifndef TASK_H 
#define TASK_H

#include <chrono>
#include <string>

// Task structure used in priority queue
struct Task {
    int id;                      // Task ID
    int priority;                // Lower number = higher priority
    int execution_time;          // Execution time in milliseconds
    std::chrono::steady_clock::time_point arrival_time;  // Time when task was added
    int waiting_time = 0;        // Accumulated waiting time in ms

    Task(int id_, int prio_, int exec_time_)
        : id(id_), priority(prio_), execution_time(exec_time_) {
        arrival_time = std::chrono::steady_clock::now();
    }

    // For priority_queue: lower priority value comes first
    bool operator<(const Task& other) const {
        return priority > other.priority;
    }
};

#endif
