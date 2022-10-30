# 2.24: Tracing System Calls for a C Program
## Question:

In Section 2.3, we described a program that copies the contents of one file to a destination file. 
This program works by first prompting the user for the name of the source and destination files. 
Write this program using either the POSIX or Windows API. 
Be sure to include all necessary error checking, including ensuring that the source file exists.

Once you have correctly designed and tested the program, if you used a system that supports it, run the program using a utility that traces system calls. Linux systems provide the strace utility, and macOS systems use the dtruss command. (The dtruss command, which actually is a front end to dtrace, requires admin privileges, so it must be run using sudo.) 
These tools can be used as follows (assume that the name of the executable file is FileCopy:

> **Linux:**  strace ./FileCopy

> **macOS:**  sudo dtruss ./FileCopy
              
Since Windows systems do not provide such a tool, you will have to trace through the Windows version of this program using a debugger.

## Approach:
Ubuntu(WSL) has been used for executing the strace commands in the terminal.
> WSL is Windows Subsystem for Linux which is a layer which is used for natively running Linux commands on Windows machines.

### Description of Files: 
1. The program that copies the contents of one file to a destination file is written in **C Language** and is named as [**copy_paste_content.c**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/copy_paste_content.c)
2. The file whose content is copied is named [**source.txt**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/source.txt) and the file where the content is copied to is named as [**destination.txt**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/destination.txt).
3. The compiled C Program gives us an object file which has been named as [**output.o**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/output).

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
    >*strace -c -osyscall_log_count ./output.o*
    
### The C Program: [**copy_paste_content.c**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/copy_paste_content.c)

Prompting the user for the name of the source file:
```
FILE *fptr1, *fptr2;
char filename[100], c;
printf("Enter the filename to open for reading \n");
scanf("%s", filename);
```

Here we define 2 pointers to FILE type and they will be assigned the address of a file descriptor, that is, an area of memory that will be associated with an input or output stream.

Opening Source File for Reading
Including all necessary error checking, ensuring that the source file exists:
```
// Open one file for reading
fptr1 = fopen(filename, "r");
if (fptr1 == NULL)
{
  printf("Cannot open file %s \n", filename);
  exit(0);
}
```
Prompting the user for the name of the destination file:
```
printf("Enter the filename to open for writing \n");
scanf("%s", filename);
```

Opening Destination File for Writing
Including all necessary error checking, ensuring that the destination file exists:
```
// Open another file for writing
fptr2 = fopen(filename, "w");
if (fptr2 == NULL)
{
  printf("Cannot open file %s \n", filename);
  exit(0);
}
```

Reading Content from Source File and Pasting it into Destination file.
```
// Read contents from file
c = fgetc(fptr1);
while (c != EOF)
{
  fputc(c, fptr2);
  c = fgetc(fptr1);
}
```
Closing the file pointers:
```
printf("\nContents copied to %s", filename);
  
    fclose(fptr1);
    fclose(fptr2);
```


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
* The number of bytes read is returned (0 indicates EOF), and the file position is advanced by this number.

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
* On success, the number of bytes written is returned. On error -1 is returned, and errno is set to indicate the error.

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
* On success, execve() returns 0, on error -1 is returned,and errno is set to indicate the error.

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

In the above 4 openat() statements:
* If pathname is relative and dirfd is the special value AT_FDCWD, then pathname is interpreted relative to the current working directory of the calling process
* The pathnames are given as arguments.
* Flags are O_RDONLY|O_CLOEXEC, O_RDONLY, O_WRONLY|O_CREAT|O_TRUNC
* mode_t mode is given as 0666
* Returned values are used as the **file descriptor** arguments for all the respective system calls.

### 5. **close():** 
```
int close(int fd);
```
Line 8 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
close(3)                                = 0
```
Line 24 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
close(3)                                = 0
```
Line 427 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
close(3)                                = 0
```
Line 429 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
close(4)                                = 0
```

In the above 4 close() statements:
* close() returns 0 on success and -1 on error
* int fd is the file descriptor which is to be closed.
> 3 was the file descriptor of "/etc/ld.so.cache" , "/lib/x86_64-linux-gnu/libc.so.6" , "source.txt" and 4 was the file descriptor of "destination.txt".
Refer [4. openat()](https://github.com/VincentPaulV/CS252-OS-Assignment/tree/main/Q1-2.24#4-openat)

### 6. **fstat():** 
```
int fstat(int fildes, struct stat *buf);
```
Line 6 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
fstat(3, {st_mode=S_IFREG|0644, st_size=32876, ...}) = 0
```
Line 14 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
fstat(3, {st_mode=S_IFREG|0755, st_size=2029592, ...}) = 0
```
Line 30 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x1), ...}) = 0
```
Line 34 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
fstat(0, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x1), ...}) = 0
```
Line 40 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
fstat(3, {st_mode=S_IFREG|0777, st_size=98293, ...}) = 0
```
Line 42 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
fstat(4, {st_mode=S_IFREG|0777, st_size=0, ...}) = 0
```

In the above 6 pread64() statements:
* The fstat() function shall obtain information about an open file associated with the file descriptor fildes, and shall write it to the area pointed to by buf.
* **int filedes** contains the file descriptor
* struct stat *buf is a buffer pointing to a struct stat:

  * If *fildes* references a shared memory object:
    
    The implementation
       shall update in the stat structure pointed to by the buf argument the st_uid, st_gid, st_size, and st_mode fields.

  * If *fildes* references a typed memory object:
    
    The implementation
       shall update in the stat structure pointed to by the buf argument the st_uid, st_gid, st_size, and st_mode fields.
* fstat() returns 0 on success and -1 on error
      
### 7. **mmap():** 
```
void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
```
Line 7 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
mmap(NULL, 32876, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fa8cb3aa000
```
Line 15 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fa8cb3a8000
```
Lines 19-23 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
mmap(NULL, 2037344, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fa8cb1b6000

mmap(0x7fa8cb1d8000, 1540096, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x22000) = 0x7fa8cb1d8000

mmap(0x7fa8cb350000, 319488, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x19a000) = 0x7fa8cb350000

mmap(0x7fa8cb39e000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7fa8cb39e000

mmap(0x7fa8cb3a4000, 13920, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fa8cb3a4000
```

In the above 7 mmap() statements:
* void *addr contains the pointer to the starting address for the new mapping.
  * If addr is NULL:
    * Kernel chooses the address at which to create the mapping. This is the most portable method of creating a new mapping
  * If addr is not NULL:
    * Kernel takes it as a hint about where to place the mapping
  
* size_t length argument specifies the length of the mapping
* int prot is  the desired memory protection of the mapping which are PROT_READ, PROT_WRITE, PROT_EXEC, PROT_NONE or a bitwise combination of them.
* int flags is the argument determines whether updates to the mapping are visible to other processes mapping the same region, and whether updates are carried through to the underlying file.
* Flags can be be of many types out of which a few are MAP_PRIVATE, MAP_FIXED, MAP_ANONYMOUS, MAP_DENYWRITE etc.
* int fd is the file descriptor
  >3 in the case of the reading of the "source.txt" file
* The contents of a file mapping, are initialized using length bytes starting at offset offset in the file (or other object)
referred to by the file descriptor fd.  
  > Offset must be a multiple of the page size
* Returns a pointer to the mapped area.  On error, the value MAP_FAILED (that is, (void *) -1) is returned, and errno is set to indicate the error.

### 8. **pread64():** 
```
ssize_t pread(int fd, void *buf, size_t count, off_t offset);
```
Lines 11-13 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
pread64(3,"\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784

pread64(3,"\4\0\0\0\20\0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0", 32, 848) = 32

pread64(3,"\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\30x\346\264ur\f|Q\226\236i\253-'o"..., 68, 880) = 68
```
Lines 16-18 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
pread64(3,"\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784

pread64(3,"\4\0\0\0\20\0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0", 32, 848) = 32

pread64(3,"\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\30x\346\264ur\f|Q\226\236i\253-'o"..., 68, 880) = 68
```

In the above 6 pread64() statements:
* The pread64() function pread() reads up to *int count* bytes from file descriptor *int fd* at *off_t offset* (from the start of the file) into the buffer starting at *buf*. The file offset is not changed.

* pread64() returns the number of bytes read and returns 0 at EOF.

### 9. **brk():** 
```
int brk(void *addr);
```
Line 2 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
brk(NULL)                               = 0x55e4f9ea9000
```
Line 31 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
brk(NULL)                               = 0x55e4f9ea9000
```
Line 32 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
brk(0x55e4f9eca000)                     = 0x55e4f9eca000
```
In the above 3 brk() statements:
* brk() sets the end of the data segment to the value specified by void *addr, when that value is reasonable, the system has enough memory, and the process does not exceed its maximum data size.
* 0x55e4f9ea9000 is the address in our case.

### 10. **mprotect():** 
```
int mprotect(void *addr, size_t len, int prot);
```
Lines 26-28 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
mprotect(0x7fa8cb39e000, 16384, PROT_READ) = 0
mprotect(0x55e4f99cf000, 4096, PROT_READ) = 0
mprotect(0x7fa8cb3e0000, 4096, PROT_READ) = 0
```
In the above 3 mprotect() statements:
* mprotect() changes the access protections for the calling process's memory pages containing any part of the address range in the interval [addr, addr+len-1]
* *int prot* is the desired memory protection needed as discussed in [**mmap()**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/README.md#7-mmap)
* Returns 0 on succesful execution and -1 on errors.


### 11. **arch_prctl():** 
```
#include <asm/prctl.h> //Definition of ARCH_* constants
#include <sys/syscall.h> //Definition of SYS_* constants
#include <unistd.h>

int syscall(SYS_arch_prctl, int code, unsigned long addr);
int syscall(SYS_arch_prctl, int code, unsigned long *addr);
```
Line 3 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
arch_prctl(0x3001 /* ARCH_??? */, 0x7ffe0279a1b0) = -1 EINVAL (Invalid argument)
```
Line 25 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
arch_prctl(ARCH_SET_FS, 0x7fa8cb3a9540) = 0
```
In the above 2 arch_prctl() statements:
*  arch_prctl() sets architecture-specific process or thread state.
   *int code* selects a subfunction and passes argument *addr* to it.
* addr is interpreted as either an unsigned long for the "set" operations, or as an unsigned long *, for the "get" operations.

> Line 3 gives us an error with error code EINVAL which indicates that code is not a valid subcommand i.e. ARCH_???

> Line 25 uses ARCH_SET_FS as the code, hence "setting" the 64-bit base for the FS register to address 0x7fa8cb3a9540.

### 12. **munmap():** 
```
int munmap(void *addr, size_t length);
```
Line 29 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
munmap(0x7fa8cb3aa000, 32876)           = 0
```
In the above munmap() statement:
* The munmap() system call deletes the mappings for the specified address range, and causes further references to addresses within the range to generate invalid memory references.
  >Here we are unmapping 0x7fa8cb3aa000, 32876 which was mapped in Line 7
  ```
  mmap(NULL, 32876, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fa8cb3aa000
  ```

* The region is also automatically unmapped when the process is terminated.


  >Closing the file descriptor does not unmap the region.

### 13. **access():** 
```
int access(const char *pathname, int mode);
```
Line 4 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
```
In the above access() statement:
* access() checks whether the calling process can access the file *pathname*.
*  herewe are trying to access *pathname* = "/etc/ld.so.preload" with mode as R_OK (testing whether the file exists and grants read operation).

  >Here we are getting error as EN0ENT 
  i.e. A component of pathname does not exist or is a dangling symbolic link.

### 14. **lseek():** 
```
off_t lseek(int fd, off_t offset, int whence);
```
Line 431 of [**syscall_log**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/syscall_log)
```
lseek(0, -1, SEEK_CUR)                  = -1 ESPIPE (Illegal seek)
```
In the above lseek() statement:
* lseek() repositions the file offset of the open file description associated with the file descriptor fd to the argument offset according to the directive whence
* Here the whence is is SEEK_CUR and the file offset is set to its current location plus offset bytes.
* lseek() returns the resulting offset location as measured in bytes from the beginning of the file.On error, the value (off_t) -1 is returned and errno is set to indicate the error.

  >Here we are getting error as ESPIPE
  i.e. fd is associated with a pipe, socket, or FIFO.

## References:
### Information and Reference of System Calls:
* https://man7.org/linux/man-pages/man2/
### The C Program:
* https://www.geeksforgeeks.org/c-program-copy-contents-one-file-another-file/

  
