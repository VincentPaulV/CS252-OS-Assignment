# CS252-OS-Assignment

# [Question 1: Chapter 2 - 2.24](https://github.com/VincentPaulV/CS252-OS-Assignment/tree/main/Q1-2.24)

##  Introducing System Calls
When you are given a task like picking up a pen from a table what is the whole thing that your brain does to make you complete it?

It takes in the task statement as a command, processes it, asks your hand to perform the function of picking up the pen and terminates the task.

That's exactly how system calls work in the Operating Systems we use today.

The task of picking up a pen can be said in any language you understand , the brain creates an impulse which your body understands and asks your hand to complete the task.

The impulse that your brain sends and only your body uderstands is pretty much what a system call does in an Operating System.

To formally address the definition of a system call we can say that:

> "System Calls are the programming interface to the services provided by the Operating System."

Generally being written in C or C++ most of the System Calls are accessed by programs via a high level Application Program Interface (API) rather than directy using the system call.

>In the above analogy of human picking up a pen, the instruction of "picking up of a pen" said in whatsoever language which you understand is the analogy to API's as in the Operating Systems.

>In fact even *printf()* in C Language is an API to call *write()* in UNIX systems or *WriteFile()* in Windows

### System Call Implementation:

Typically a number is associated with each system call and **System Call Interface** maintains a table indexed according to these numbers.

The System Call Interface invokes the system call intended in the Kernel(the part of the Operating System that always runs) and returns status of the system of system call and any return values.

So the System Call Interface is defined in such a way that the user need not know how the system call is implemented hence just needing to obey the *API* and understand what the OS would do as a result call.

Most of the details of OS interface hidden from the programmer by API and are managed by run time support library.

>A run time support library is set of functions built into libraries included with compiler realizing the many functions by accessing the Operating System which is compiler dependent.

### API - System Call - OS Relationship

![API-System Call-OS Relationship](/images/api_os_relation.png)

## Motivation for [2.24](https://github.com/VincentPaulV/CS252-OS-Assignment/tree/main/Q2-4.22)

Here we have a program which copies the content of one file to a destination file.
Then we use a utility that traces system calls.
>In this case we use *strace*

As we have a basic idea about System Calls and what they mean, we can delve into understanding what the actual system calls made are.

By analyzing the system calls log we can deeply understand what exactly the OS does when it comes to the system calls made and how our program actually works!




# [Question 2: Chapter 4 - 4.22](https://github.com/VincentPaulV/CS252-OS-Assignment/tree/main/Q2-4.22)

## Threads - A Synopsis
The most simplest way to define a thread would be to say that:
> "Threads are a segment of a process and run within a process."

So it's safe to say that multiple tasks within an application can be implemented by seperate threads.

Naming a few tasks which a thread would likely perform within an application would include:
* Update display
* Fetch data
* Spell checking
* Answer a network request

So why do we make a thread for a process?

Thread creation is light-weight relative to Process Creation which is heavy-weight and hence for many of the real time cases making threads within a process rather than "forking" a new process and thus making it more efficient than creating a new process.

Hence we can agree to the fact that
> Threads simplify code, increase efficiency and it can be observed that generally kernels are multithreaded

### Single Threaded and Multi Threaded Processes:

![Multi-Thread vs Single Thread](/images/multi_thread_process.png)
### Why do we make Threads?
Some of the major benfits we have are:
* **Responsiveness:** May allow continued execution if part of process is blocked, especially important for user interfaces
* **Resource Sharing:** Threads share resources of process, easier than shared memory or message passing as observed in Inter-Process Communication
* **Economy:** It is cheaper than process creation, thread switching has lower overhead than context switching

   > Thread switching is observed when we see the output of [**4.22**](https://github.com/VincentPaulV/CS252-OS-Assignment/tree/main/Q2-4.22)
* **Scalability:** helps us take the essence of multi-core architecture

### User Threads and Kernel Threads:

**User threads:** Here the management is done by user-level threads library
  
  Three primary thread libraries:
  * POSIX Pthreads
  * Windows threads
  * Java threads

**Kernel threads:** These threads are supported by the Kernel

  Virtually all general-purpose operating systems, including:
  * Windows
  * Linux
  * Mac OS X
  * iOS
  * Android *etc*

## Motivation for [**4.22**](https://github.com/VincentPaulV/CS252-OS-Assignment/tree/main/Q2-4.22)

Here we make threads for different computational processes mentioned (i.e. average, minimum, and maximum) using [**POSIX Threads**](https://github.com/VincentPaulV/CS252-OS-Assignment#user-threads-and-kernel-threads).

As we've seen the usage of threads could prove beneficial when it comes to **Responsiveness**, **Resource Sharing**, **Economy**, **Scalability**, with this rather simple program we can understand the essence of thread-making with the strings of the benefits sliding over.

## References:
- CS252 Lecture Notes
- 10th edition of Operating System Concepts by Abraham Silberschatz, Peter Baer Galvin and Greg Gagne.

## Author:
Vincent Paul Veernapu
201ME365








