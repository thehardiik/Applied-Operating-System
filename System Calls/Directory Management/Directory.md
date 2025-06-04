## Directory Management


### 1. Mkdir()

The mkdir() system call creates a new directory with the specified name and permissions.

It is similar to the shell command:

    mkdir myfolder

#### Syntax:

    int mkdir(const char *pathname, mode_t mode);

#### Parameters:

    pathname: The name (or full path) of the directory you want to create.

    mode: Permissions (like 0755) specifying read/write/execute rights.

    ⚠ The mode is affected by the process’s umask, which may mask out some permission bits.

#### Return Value:

    On success: Returns 0

    On failure: Returns -1 and sets errno

#### Example: 
    
    In mkdir.c

### 2. Rmdir()

The rmdir() system call removes (deletes) an empty directory.

It is similar to the shell command:

    rmdir myfolder

#### Syntax:

    int rmdir(const char *pathname);

#### Parameters:

    pathname: Path to the directory to remove.

    ⚠ The directory must be empty (no files or subdirectories inside).

#### Return Value:

    On success: Returns 0

    On failure: Returns -1 and sets errno

#### Example:

    In rmdir.c

### 3. Link()

The link() system call creates a new hard link to an existing file.
A hard link is essentially another name for the same file — both entries point to the same inode (same physical data on disk).
So, deleting one does not delete the actual data as long as another hard link exists.

#### Syntax:

    int link(const char *existing_path, const char *new_path);

#### Parameters:

    existing_path: Path to the existing file.

    new_path: Path where the new hard link will be created.

#### Return Value:

    On success: Returns 0

    On failure: Returns -1 and sets errno

#### Example:

Explore it

    #include <unistd.h>
    #include <stdio.h>

    int main() {
        int status = link("file1.txt", "hardlink_to_file1.txt");
        if (status == 0) {
            printf("Hard link created successfully!\n");
        } else {
            perror("link");
        }
        return 0;
    }

### 4. Mount()

The mount() system call attaches a filesystem (like ext4, FAT32, etc.) to a mount point in the directory hierarchy, making its files accessible.

#### What does "mounting" mean?

In UNIX-like systems (like Linux), there is a single unified file system tree rooted at /.
Every file or directory you access is part of this tree.

Mounting is the process of attaching a new filesystem (from a device like a USB stick or partition) into this tree at a specific mount point (a directory, like /mnt/usb).

#### Syntax: 


    int mount(const char *source, const char *target,
            const char *filesystemtype, unsigned long mountflags,
            const void *data);

#### Parameters:

| Parameter        | Meaning                                                 |
| ---------------- | ------------------------------------------------------- |
| `source`         | Device or special file (e.g. `/dev/sdb1`)               |
| `target`         | Directory where it should be mounted (mount point)      |
| `filesystemtype` | e.g., `"ext4"`, `"vfat"`, `"ntfs"`                      |
| `mountflags`     | Options like `MS_RDONLY` (read-only), `MS_NOEXEC`, etc. |
| `data`           | Optional filesystem-specific data (can be NULL)         |

#### Return Value:

    On success: Returns 0

    On failure: Returns -1 and sets errno

#### Example (Try it out):

    ⚠ Requires root privileges.

    #include <sys/mount.h>
    #include <stdio.h>

    int main() {
        if (mount("/dev/sdb1", "/mnt/usb", "vfat", 0, NULL) == 0) {
            printf("Mounted successfully!\n");
        } else {
            perror("mount");
        }
        return 0;
    }

### 5. Chdir()

The chdir() system call changes the current working directory of the calling process.

This is equivalent to the shell command:

    cd /path/to/directory

#### Syntax:

    int chdir(const char *path);

#### Parameters:

    path: The new directory path you want to move into.

        Can be absolute (/home/user/docs) or relative (../folder)

#### Return Value:

    0 → on success

    -1 → on failure, and errno is set

#### Example 

    Self Explanatory.

### 6. Chroot()

The chroot() system call changes the root directory (/) for the current running process.

After chroot("/newroot"), the process sees /newroot as / — it cannot see or access anything outside this new root directory.

    🛡 It’s often used for security isolation (jails, sandboxes) or creating minimal environments for testing or recovery.

#### Syntax:

    int chroot(const char *path);

#### Parameters:

    path: A directory path that becomes the new root (/) for the process.

#### Return Value:

    0 → on success

    -1 → on failure, and sets errno










