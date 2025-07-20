# RealTimeTaskScheduler
A C++ implementation of a real-time task scheduler using priority queues and multithreading. This project demonstrates how to manage tasks dynamically, ensuring efficient execution based on priority. Features

Priority Queues: Tasks are managed using a priority queue (std::priority_queue), ensuring tasks with higher priority are executed first.
Multithreading: Tasks are executed concurrently using a separate thread (std::thread).
Task Preemption: Not directly implemented, but can be achieved by interrupting tasks and resuming them later.
Starvation Handling: Implemented through an aging mechanism that gradually increases the priority of waiting tasks.
Aging Mechanism: A simple aging policy updates task priorities over time to prevent starvation.