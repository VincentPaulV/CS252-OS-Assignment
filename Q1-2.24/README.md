# 2.24: Tracing System Calls for a C Program
## Question:

In Section 2.3, we described a program that copies the contents of one file to a destination file. 
This program works by first prompting the user for the name of the source and destination files. 
Write this program using either the POSIX or Windows API. 
Be sure to include all necessary error checking, including ensuring that the source file exists.

Once you have correctly designed and tested the program, if you used a system that supports it, run the program using a utility that traces system calls. Linux systems provide the strace utility, and macOS systems use the dtruss command. (The dtruss command, which actually is a front end to dtrace, requires admin privileges, so it must be run using sudo.) 
These tools can be used as follows (assume that the name of the executable file is FileCopy:

>Linux:  strace ./FileCopy

>macOS:  sudo dtruss ./FileCopy
              
Since Windows systems do not provide such a tool, you will have to trace through the Windows version of this program using a debugger.

## Approach:
Ubuntu(WSL) has been used for executing the strace commands in the terminal.
> WSL is Windows Subsystem for Linux which is a layer which is used for natively running Linux commands on Windows machines.

### Description of Files: 
1. The program that copies the contents of one file to a destination file is written in **C Language** and is named as [**copy_paste_content.c**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/copy_paste_content.c)
2. The file whose content is copied is named [**source.txt**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/source.txt) and the file where the content is copied to is named as [**destination.txt**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/destination.txt).
3. The compiled C Program gives us an object file which has been named as [**output.o**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/output.o).

**Command:** 
>*gcc -o output.o copy_paste_content.c*

### Description of Logs:
1. [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log) contains all the system calls made by the program during its total runtime.
  **Command:** 
  >*strace -osyscall_log ./output.o*
2. [**syscall_log_initial**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log_initial) contains all the system calls made by the program before the [**source.txt**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/source.txt) has been entered for reading.
3. [**syscall_log_read**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log_read) contains all the system calls made by the program after [**source.txt**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/source.txt) has been input and [**destination.txt**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/destination.txt) has to be entered
4. [**syscall_log_count**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log_count) is a systematic log file which contains the time distribution of all system calls made, giving better readability.
  **Command:** 
  >*strace -c -osyscall_log ./output.o*

### [**copy_paste_content.c**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/copy_paste_content.c)
This program works by first prompting the user for the name of the source and destination files.


## List of System Calls made:
### 1. **read():** 
```
ssize_t read(int fd, void *buf, size_t count);
```
Line 35 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
read(0, "source.txt\n", 1024)           = 11
```
Line 41 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
read(3, "\tSONNETS\r\n\r\n\r\n\r\nTO THE ONLY BEGE"..., 512) = 512
```
In the above 2 read() statements:
* The file descriptor(int fd) is mentioned
* The text being read is in buffer(void *buf)
* The count (size_t - unsigned integer in POSIX) is 512 or 1024 bytes read.

### 2. **write():** 
```
ssize_t write(int fd, const void *buf, size_t count);
```
Line 33 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
write(1, "Enter the filename to open for r"..., 40) = 40
```
Line 44 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
write(4, "\tSONNETS\r\n\r\n\r\n\r\nTO THE ONLY BEGE"..., 512) = 512
```
In the above 2 write() statements:
* The file descriptor(int fd) is mentioned
* The text being wriiten is in buffer(void *buf)
* The count (size_t - unsigned integer in POSIX) is **upto** 512 bytes read (40 in the case of Line 33).

### 3. **execve():** 
```
int execve(const char *pathname, char *const argv[],char *const envp[]);
```
Line 1 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
execve("./output.o", ["./output.o"], 0x7ffe8e964f88 /* 24 vars */) = 0
```

In the above execve() statement:
* The path name is the object file to be executed
* *argv* is an array of pointers to strings passed to the new program as its command-line arguments (in the above case is "output.o").
* *envp* is an array of pointers to strings, conventionally of the form key=value, which are passed as the environment of the new program.The envp array must be terminated by a NULL pointer(in our case is a hexadecimal address).

### 4. **openat():** 
```
int openat(int dirfd, const char *pathname, int flags);
int openat(int dirfd, const char *pathname, int flags, mode_t mode);
```
Line 5 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
```
Line 9 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
```
Line 36 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
openat(AT_FDCWD, "source.txt", O_RDONLY) = 3
```
Line 39 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
openat(AT_FDCWD, "destination.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 4
```

In the above openat() statement:
* If pathname is relative and dirfd is the special value AT_FDCWD, then pathname is interpreted relative to the current working directory of the calling process
* The pathnames are given as arguments.
* Flags are O_RDONLY|O_CLOEXEC, O_RDONLY, O_WRONLY|O_CREAT|O_TRUNC
* mode_t mode is given as 0666
* Returned values are used as the **file descriptor** arguments for read() and write() statements.
