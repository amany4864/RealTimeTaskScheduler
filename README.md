# RealtimeTaskScheduler

A multithreaded C++ project that simulates a real-time task scheduler using priority-based scheduling with an aging mechanism to prevent starvation. Tasks are submitted interactively, executed concurrently, and monitored in real-time.

---

## 🚀 Features

- 🧵 **Multithreaded execution** using C++ `std::thread`
- ⏫ **Priority-based scheduling** (higher number = higher priority)
- ⏳ **Aging mechanism** to prevent starvation
- 📟 **Interactive command-line interface**
- 👀 **Live task status display**
- ✅ **Graceful shutdown and cleanup**

---

## 🗂️ Project Structure

```
RealtimeTaskScheduler/
├── Makefile
├── include/
│   ├── logger.h
│   ├── scheduler.h
│   └── task.h
├── src/
│   ├── main.cpp
│   ├── scheduler.cpp
│   ├── task.cpp
│   └── worker.cpp
└── utils/
    └── logger.cpp
```

---

## 🧠 Core Components

### 📦 Task

- Defined in `task.h` and `task.cpp`
- Attributes:
  - `id`, `priority`, `execution_time`, `arrival_time`, `waiting_time`
- Comparable by priority for the task queue

### 📋 Scheduler

- Defined in `scheduler.h` and `scheduler.cpp`
- Manages:
  - Task queue (`std::priority_queue`)
  - Worker threads
  - Aging of tasks
- Key methods:
  - `addTask()`
  - `getTask()`
  - `printStatus()`
  - `start()`, `stop()`

### 🔧 Worker

- Logic defined in `worker.cpp`
- Each thread:
  - Waits on condition variable
  - Picks task from queue
  - Simulates execution with `std::this_thread::sleep_for`
  - Logs execution details

### 🖥️ CLI Interface

- Controlled via `main.cpp`
- Commands supported:
  - `add <id> <priority> <execution_time(ms)>`
  - `status`
  - `exit`

---

## 🧠 Scheduling Logic

- Tasks scheduled by priority (higher = earlier)
- Tasks older than threshold get **boosted** priority (aging)
- Uses `std::mutex` and `std::condition_variable` for concurrency control
- Prevents starvation and ensures fairness

---

## 🛠️ Build Instructions

### Requirements

- `g++` with C++17 or newer
- `make`

### Build & Run

```bash
make clean
make
./scheduler
```

---

## 🧪 Example Usage

### Commands:

```bash
add 1 4 4000
add 2 2 2000
add 3 5 3000
add 4 1 1000
add 5 3 3500
status
exit
```

### Sample Output:

```
[Scheduler] Task 1 added with priority 4 and time 4000ms
[Worker 0] Executing Task 3 with priority 5
[Status]
Pending Tasks:
Task ID: 4 | Priority: 1 | Exec Time: 1000ms | Waiting Time: 2000ms
[Worker 1] Idle
[Aging] Boosted Task 4 to priority 2
```

## 🌱 Possible Extensions

- ❌ Cancel or remove task by ID
- ⏸️ Pause/resume execution
- 📝 File-based logging
- 🌐 Web dashboard
- 🔌 REST API for remote scheduling

---

## 📌 Summary

This project simulates a real-time task scheduler with clean C++ multithreading and scheduling logic. It demonstrates how concurrency, fairness, and system resource handling come together to simulate OS-level behavior in a simplified environment.

---

