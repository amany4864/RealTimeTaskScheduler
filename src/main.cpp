#include <iostream>
#include <sstream>
#include <string>
#include "scheduler.h"

int main() {
    Scheduler scheduler(2);
    scheduler.start();

    std::string line;
    std::cout << ">> ";
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "add") {
            int id, prio, exec;
            if (iss >> id >> prio >> exec) {
                scheduler.addTask(id, prio, exec);
                std::cout << "Task added.\n";
            } else {
                std::cout << "Usage: add <id> <priority> <execution_time_ms>\n";
            }
        } else if (cmd == "status") {
            scheduler.printStatus();
        } else if (cmd == "exit") {
            break;
        } else if (!cmd.empty()) {
            std::cout << "Unknown command: " << cmd << "\n";
        }

        std::cout << ">> ";
    }

    scheduler.stop();
    return 0;
}
