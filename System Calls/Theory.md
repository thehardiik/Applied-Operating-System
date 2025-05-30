# System Calls

A system call is a way for a program (user-level process) to request a service from the operating system kernel.

### Why System Calls ?

User programs (like Chrome, VLC, etc.) cannot directly access hardware (like CPU, disk, memory) for security and stability. So, they ask the OS to do it through system calls.

## System Calls for Process Management.

### What is Process

A process is a program in execution. The OS manages processes using system calls to:

    * Create new processes
    * End existing ones
    * Switch between them
    * Wait for other processes
    * Share or pass data

### 1. Fork ()

fork() is a system call used to create a new process by duplicating the calling (parent) process.
The newly created process is called the child process.

Key Points:

    * The child gets a copy of the parent’s memory, file descriptors, and    program counter.

    * Both processes continue executing from the point of the fork() call.

    * Return value of fork() tells you which process you're in:

        0 → Child process

        Positive PID → Parent process (value is child’s PID)

        -1 → Fork failed

✅ In the parent process:

    fork() returns the PID of the child.

    getpid() returns the PID of the parent (itself).

✅ In the child process:

    fork() returns 0.

    getpid() returns the PID of the child (itself).

