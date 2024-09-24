# MCP Process Scheduler: Ghost in the Shell

### Overview
This project implements a **Master Control Program (MCP)** that manages multiple processes through scheduling, signals, and resource monitoring. Inspired by both philosophical concepts and advanced operating system design, this project showcases fundamental OS concepts such as **multiprocessing**, **signal handling**, and **process scheduling**.

The project is structured in multiple phases, each demonstrating incremental complexity and providing hands-on experience with key system-level programming challenges.

---

### Features
- **Process Creation and Management**: The MCP launches a set of processes based on commands from an input file, simulating real-world process handling.
- **Custom Scheduling Algorithm**: Implemented a round-robin scheduler to manage the execution of processes in a time-sliced manner, ensuring fair CPU allocation.
- **Signal Handling**: Controlled process execution using UNIX signals (`SIGSTOP`, `SIGCONT`, and `SIGUSR1`), showcasing how processes can be started, paused, and resumed.
- **Resource Monitoring**: The MCP gathers and presents process resource usage (e.g., memory, CPU time) from the `/proc` directory, providing real-time insights similar to the Linux `top` command.

---

### Key Operating System Concepts Demonstrated
1. **Multiprocessing**:
   - The project uses **fork()** to create multiple independent processes, isolating them with separate memory spaces, demonstrating process creation and memory management at the OS level.
   - Each process runs independently, avoiding common concurrency issues seen with multithreading, such as race conditions.

2. **Process Scheduling**:
   - A time-slicing mechanism is implemented using **SIGALRM** and a custom scheduler. This shows how an OS manages CPU time between processes to ensure fairness and responsiveness.

3. **Signal Handling**:
   - Signals such as `SIGSTOP`, `SIGCONT`, and `SIGUSR1` are used to control process execution. This highlights the importance of asynchronous event handling in OS process management.

4. **Resource Monitoring and System Calls**:
   - The project collects real-time resource usage data from the **/proc** filesystem, showcasing your understanding of system-level resource tracking and process lifecycle management.

---

### Project Structure

```bash
.
├── part1.c     # MCP v1.0: Basic process launching
├── part2.c     # MCP v2.0: Process control with signals
├── part3.c     # MCP v3.0: Custom process scheduling
├── part4.c     # MCP v4.0: Resource monitoring and reporting
├── part5.c     # MCP v5.0: Adaptive scheduling (extra credit)
├── MCP.h       # Optional header for function declarations
├── Makefile    # Build automation
└── Report.pdf  # Detailed report on project implementation
```

Each phase of the project builds on the last, adding features like scheduling, signal handling, and resource monitoring.

---

### Getting Started

#### Prerequisites
- Linux operating system (or a Linux virtual machine)
- GCC compiler
- Make utility

#### Installation
Clone the repository and navigate to the project directory:
```bash
git clone https://github.com/YuanYuanBingZi/mcp-process-scheduler.git
cd mcp-process-scheduler
```

To build the project, simply run:
```bash
make
```

#### Running the Project
You can run each part of the project using the following commands:

```bash
./part1 input_file.txt   # Runs MCP v1.0: Basic process launching
./part2 input_file.txt   # Runs MCP v2.0: Process control with signals
./part3 input_file.txt   # Runs MCP v3.0: Process scheduling
./part4 input_file.txt   # Runs MCP v4.0: Resource monitoring
./part5 input_file.txt   # Runs MCP v5.0: Adaptive scheduling (if implemented)
```

---

### Example Output

Running **MCP v3.0** (with process scheduling):
```bash
Process 1 started
Process 2 started
Process 1 suspended
Process 2 resumed
...
All processes completed. MCP exited.
```

---

### Challenges Faced & Solutions

1. **Process Synchronization**: Handling multiple processes concurrently and ensuring proper control over their execution with signals was a key challenge. The solution was leveraging UNIX signals effectively to pause and resume processes based on the MCP scheduler’s control.
   
2. **Efficient Resource Management**: Ensuring the processes were properly tracked and their resource usage reported required deep understanding of system calls and the `/proc` filesystem. Analyzing the data and presenting it in a human-readable format was critical for both the project's success and its practicality.

3. **Scheduling Precision**: Implementing time-slicing with high precision without relying on `sleep()` for delays involved mastering signal alarms and correctly interrupting process execution to swap CPU time between tasks.

---

### Why This Project Is Important

This project demonstrates advanced OS-level programming skills, including process creation, control, and scheduling, all crucial for roles in systems programming, performance optimization, and low-level software engineering. By building this from scratch, I've gained a deeper understanding of how operating systems manage resources and ensure process isolation and execution.

---

### Future Enhancements
- **Priority-based Scheduling**: Implementing more sophisticated scheduling algorithms, such as priority-based scheduling or weighted round-robin, to further optimize process management.
- **Advanced Resource Analysis**: Adding more in-depth analysis and visualizations of process resource consumption (e.g., graphs of CPU usage over time).

---

### Conclusion

This project highlights my ability to work on complex system-level problems, break them down into modular phases, and deliver robust, well-documented code. It showcases not only my understanding of operating systems but also my problem-solving abilities, attention to detail, and capacity to manage resource-constrained environments.

---

### Contact Information

If you'd like to discuss the project, feel free to reach out via [LinkedIn](https://www.linkedin.com/in/tongg/) or [email](yuanyuanbingzi@gmail.com).

---
