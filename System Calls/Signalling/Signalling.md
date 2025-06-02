## Signalling

Signalling is a mechanism used to send notifications between processes or threads.
It is used to:

    * Notify a process of an event (like termination, interruption, or a specific condition).

    * Signals are asynchronous notifications sent to a process.

    * Example: SIGINT, SIGKILL, SIGTERM, SIGCHLD

    * Sent by: OS, another process, or user input (like Ctrl+C).

    * Handled by: default action, ignored, or with a custom signal handler.

### What happend when we press 'ctrl + C' ?

When you press Ctrl + C in a terminal, it sends a special signal called SIGINT (short for Signal Interrupt) to the foreground process running in that terminal.

🔍 What exactly happens?

1. Interrupt Signal Sent:

        * The terminal (usually a shell like bash) sends SIGINT (signal number 2) to the process.

        * This is an asynchronous signal, meaning it can be delivered at any time.

2. Process Receives SIGINT:

        * If the process has no custom handler, it will terminate immediately (default behavior).

        * If the process handles SIGINT (using a signal handler), it can:

            * Clean up resources.

            * Prompt the user.

            * Ignore the signal (not recommended).

            * Log information.

3. Shell Regains Control:

        * After the process stops, the shell takes back control and shows a new prompt.

### 1. Sigaction()

Sigaction() is a system call in Unix/Linux used to define how a process should handle a specific signal—like SIGINT, SIGTERM, etc.

Syntax:

    #include <signal.h>

    int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

    

signum: the signal number (e.g. SIGINT)

act: pointer to sigaction struct with new settings

oldact: (optional) pointer to save the previous handler

### 2. Sigpending()

Sigpending() is a system call in Unix/Linux that checks which signals are currently pending (i.e., delivered but not yet handled) for the calling process.

    * sigpending() shows which signals are waiting to be delivered.

    * Useful for debugging, or delaying signal handling.

    * Works together with sigprocmask() (used to block/unblock signals).

### 3. Sigprocmask()

* sigprocmask() is a system call in Unix/Linux used to block or unblock signals from being delivered to a process.

* It controls the signal mask of the calling process — the set of signals currently blocked (i.e., signals that are temporarily held and not delivered until unblocked).

### 4. SIG_IGN and SIG_DFN

#### SIG_IGN : 

    SIG_IGN is a symbolic constant in C that tells the system to ignore a signal.

#### SIG_DFN : 

    SIG_DFL stands for "default action". It is a symbolic constant in C used to restore the default behavior for a signal.

### Disecting backgroun process.

When you run a command with & at the end, it executes in the background.

This means the shell does not wait for the command to finish — it gives you a prompt back immediately.

command &

    Step 1 :- Shell forks a child.
    Step 2 :- sigaction(SIGINT, SIG_IGN, NULL) / sigaction(SIGQUIT, SIG_IGN, NULL)
    Step 3 :- Runs the command using exec.

In the parent shell process, signals like SIGINT (Ctrl+C) and SIGQUIT (Ctrl+) are ignored for the child process group because the background job shouldn’t be interrupted by the terminal signals meant for the foreground job.

#### Q: Then how a background process can be stopped ?
ANS: By usign SIGKILL

### 5. SIGKILL

SIGKILL is a special, powerful signal in Unix/Linux used to immediately terminate a process.

Key facts about SIGKILL:

* Signal number: 9

* Effect: Forces the kernel to stop and remove the process immediately, no chance for the process to catch or ignore it.

* Cannot be caught, blocked, or ignored — unlike most other signals.

* Used when you want to forcefully kill a misbehaving or unresponsive process.

### 6. SIGALARM

SIGALRM is a signal sent to a process when a timer set by alarm() expires.
Key points:

* Used to notify a process that a specified amount of real time has passed.

* Typically used to implement timeouts.

* Default action: terminate the process (if not caught).

* You can catch SIGALRM to perform a specific action when the timer expires.


