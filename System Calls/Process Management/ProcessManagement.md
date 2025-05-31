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

### 2. Waidpid()

waitpid() is a system call used by a parent process to wait for a specific child process to finish execution.

What it does:

    * Suspends the calling (parent) process until the child specified by pid finishes.

    * Returns the PID of the child that exited.


| Parameter | Meaning                                                               |
| --------- | --------------------------------------------------------------------- |
| `pid`     | PID of the child to wait for. Can also use special values (see below) |
| `status`  | Pointer to an `int` where child's exit status will be stored          |
| `options` | Flags (e.g. `0` for default behavior)                                 |

### 3. Exit()


exit() is a system-level library function used to terminate a process gracefully and return an exit status to the operating system (or parent process).

    void exit(int status);

    * status = 0: Normal/successful termination

    * status ≠ 0: Indicates error or specific condition (e.g., exit(7))


🧬 What happens internally?


    * All atexit() handlers are executed (if any were registered).

    * Open file descriptors are closed.

    * Buffered output is flushed (important for printf()).

    * The exit status is returned to the parent process.

    * The OS cleans up the process (memory, etc.).

### 4. Execve()

execve() replaces the current process image with a new program.

This means:

    The process calling execve() is transformed into another program — it does not return on success.

Behavior: If execve() is called:

    * The existing code/data/heap/stack are all replaced

    * Only the PID remains the same

    * If it succeeds, the process becomes the new program

int execve(const char *pathname, char *const argv[], char *const envp[]);

Parameters:

    pathname: Full path to the executable file (e.g., /bin/ls)

    argv[]: Array of argument strings (e.g., {"ls", "-l", NULL})

    envp[]: Array of environment variables (e.g., {"PATH=/usr/bin", NULL})

Returns:

    On success: Does not return — current program is replaced

    On failure: Returns -1 and sets errno


| Step                   | What happens                     |
| ---------------------- | -------------------------------- |
| Provide `/bin/ls` path | Same executable as `ls` command  |
| Call `execve()`        | Current program replaced by `ls` |
| After `execve()`       | No code from old program runs    |
| When `ls` finishes     | Process exits or parent resumes  |


Why not call execve() in the parent?

    * execve() replaces the current process image — it completely replaces the running program with the new program.

    * If the parent calls execve(), then the parent process itself is replaced by the new program (e.g., /bin/ls), and it loses control — it can no longer run its own code afterward.

    * This means:

        * The original parent program stops running.

        * The parent cannot wait for the child or do any further work because it doesn’t exist anymore as the original program.
