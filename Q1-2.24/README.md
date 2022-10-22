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

1. The program that copies the contents the of one file to a destination file is wiritten in **C Language**
2. The file whose content is copied is named [*source.txt*](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/source.txt) and the file where the content is copied to is named as [*destination.txt*](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q1-2.24/destination.txt)
