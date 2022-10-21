# CS252-OS-Assignment

## What are System Calls?
System Calls are the programming interface to the services provided by the Operating System.

Generally being written in C or C++ most of the System Calls are accessed by programs via a high level Application Program Interface (API) rather than directy using the system call.

>In fact even *printf()* in C Language is an API to call *write()* in UNIX systems or *WriteFile()* in Windows

### System Call Implementation:

Typically a number is associated with each system call and **System Call Interface** maintains a table indexed according to these numbers.

The System Call Interface invokes the system call intended in the Kernel(the part of the Operating System that always runs) and returns status of the system of system call and any return values.

So the System Call Interface is defined in such a way that the user need nmot know how the system call is implemented hence just needing to obey the *API* and understand what the OS would do as a result call.

Most of the details of OS interface hidden from the programmer by API and are managed by run time support library (i.e. set of functions built into libraries including with compiler)

>A run time support library is set of functions built into libraries included with compiler realizing the many functions by accessing the Operating System

![API-System Call-OS Relationship](/assets/images/api_os_relation.png)


### [Question 1: Chapter 2 - 2.24](https://github.com/VincentPaulV/CS252-OS-Assignment/tree/main/Q2-4.22)

### [Question 2: Chapter 4 - 4.22](https://github.com/VincentPaulV/CS252-OS-Assignment/tree/main/Q2-4.22)




