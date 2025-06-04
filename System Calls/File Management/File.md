## System Calls for File Management

### 1. Open()

The open() system call is used in operating systems (especially Unix/Linux) to open a file and return a file descriptor, which is a small integer used to refer to the file in subsequent system calls like read(), write(), or close().

#### Syntax:

    int open(const char *pathname, int flags);
    int open(const char *pathname, int flags, mode_t mode);

##### Parameters:

    pathname: Path to the file.

    flags: How you want to open the file (e.g., read-only, write-only).

        Common flags:

            O_RDONLY – Open for reading.

            O_WRONLY – Open for writing.

            O_RDWR – Open for reading and writing.

            O_CREAT – Create the file if it does not exist.

            O_APPEND – Append to the file.

    mode (optional): Specifies the file permission bits if O_CREAT is used.

##### Return Value:

    On success: Returns a non-negative file descriptor.

    On failure: Returns -1 and sets errno.

#### Example:

    int fd = open("file.txt", O_RDWR | O_CREAT, 0644);

    if (fd == -1) {
        perror("open");
    }

#### Notes:

    1. It is a low-level file I/O operation.

    2. open() does not return a FILE* like fopen() in C; it returns an int.

    3. You must use close(fd) to close the file when done.

### 2. Read()

The read() system call is used to read data from a file (or device) into a buffer in memory. It works at a low level and uses a file descriptor, usually obtained via open().

#### Syntax:

    ssize_t read(int fd, void *buf, size_t count);

#### Parameters:

    fd: The file descriptor (returned by open()).

    buf: Pointer to a buffer where the data will be stored.

    count: Maximum number of bytes to read.

#### Return Value:

    On success: Returns the number of bytes actually read (can be less than count).

    On end of file (EOF): Returns 0.

    On failure: Returns -1 and sets errno.

#### Example:
    In ReadingFile.c

####  Key Points:

    1. read() reads raw bytes from the file.

    2. You must allocate a buffer large enough to hold the data.

    3. It is blocking by default: it waits until data is available.

    4. Useful for working with files, pipes, sockets, and devices.

### 3. Write ()

The write() system call is used in Unix/Linux to write data from a buffer to a file (or device, socket, etc.). It is a low-level I/O operation and works using a file descriptor, typically obtained from open().

#### Syntax:

    ssize_t write(int fd, const void *buf, size_t count);

##### Parameters:

    fd: The file descriptor (from open()) that points to the file/device where you want to write data.

    buf: A pointer to the buffer in memory that holds the data you want to write.

    count: The number of bytes from the buffer to write.

#####  Return Value:

    On success: Returns the number of bytes actually written.

    On failure: Returns -1 and sets errno.

    Note: It may write less than count bytes — especially with pipes, sockets, or interrupted system calls.

#### Example:

    In WritingFile.c

#### Key Points:

    1. write() sends data from memory to a file/device.

    2. Works with anything represented as a file: text files, sockets, terminals, etc.

    3. File should be opened with write permission: O_WRONLY or O_RDWR.

    4. Writing to stdout can also be done with write(1, ...), since file descriptor 1 is standard output.

### 4. Close()

The close() system call is used to release a file descriptor that was previously opened using open(). It tells the operating system that your program is done using the file, so any resources can be freed.

#### Syntax:

    int close(int fd);

#### Parameters:

    fd:
    The file descriptor you want to close (obtained from open()).

#### Return Value:

    On success: Returns 0.

    On failure: Returns -1 and sets errno.

#### Example

    All over the place.

#### Key Points:

    1. Every call to open() uses system resources (like memory and file tables).

    2. Failing to call close() can cause resource leaks.

    3. In systems with file limits (like ulimit -n), forgetting to close files may cause "too many open files" errors.

    4. Closing also flushes any pending writes to disk for writable files.

### 5. Lseek()

The lseek() system call is used to move the read/write file offset (also called the file pointer) to a specific location within an open file. This allows random access to different parts of the file.

#### Syntax:

    off_t lseek(int fd, off_t offset, int whence);

#### Parameters:

    fd:
    File descriptor (from open()).

    offset:
    Number of bytes to move the pointer. Can be positive or negative (depending on whence).

    whence:
    Tells from where the offset is applied. It can be:

    | Constant   | Meaning                    |
    | ---------- | -------------------------- |
    | `SEEK_SET` | From beginning of file     |
    | `SEEK_CUR` | From current file position |
    | `SEEK_END` | From end of file           |

#### Return Value:

    On success: Returns the new offset in bytes from the beginning of the file.

    On failure: Returns -1 and sets errno.

#### Example:

    In ReadingFile.c

#### Key Points:

    1. Commonly used for:

        * Skipping bytes

        * Overwriting parts of a file

        * Getting file size using lseek(fd, 0, SEEK_END)

    2. Cannot be used on pipes or sockets, only regular files.

### 6. Dup()

The dup() system call is used to duplicate an existing file descriptor. The new file descriptor refers to the same open file as the original, meaning they share the same file offset and open file status flags.

#### Syntax:

    int dup(int oldfd);

#### Parameters:

    oldfd: The existing file descriptor you want to duplicate.

#### Return Value:

    On success: Returns a new file descriptor (the lowest-numbered unused fd ≥ 0).

    On failure: Returns -1 and sets errno.

#### Example:

    Self Explanatory

#### Key Points:

    * Both fd and the dup()ed fd share:

        1. Same file offset (so one affects the other)

        2. Same underlying open file (same file table entry in the kernel)
