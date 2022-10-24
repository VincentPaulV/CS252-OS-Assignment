# 4.22 Writing a Multi-Threaded Program

## Question:

Write a multithreaded program that calculates various statistical values for a list of numbers. 
This program will be passed a series of numbers on the command line and will then create three separate worker threads. 
One thread will determine the average of the numbers, the second will determine the maximum value, and the third will determine the mini- mum value. 
For example, suppose your program is passed the integers 90 81 78 95 79 72 85 

The program will report
>         The average value is 82
>         The minimum value is 72
>         The maximum value is 95

The variables representing the average, minimum, and maximum values will be stored globally. 
The worker threads will set these values, and the parent thread will output the values once the workers have exited. 
(We could obviously expand this program by creating additional threads that determine other statistical values, such as median and standard deviation).

## Approach:

## List of Data Types & Functions involved in thread-making:
### **1. Data Type *pthread_t:***
```
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
```


### **2. Function *pthread_create():***
```
int pthread_create(pthread_t *__restrict__thread,const pthread_attr_t *__restrict__attr, void *(*start_routine)(void *), void *restrict arg);
```
Lines 94-98 in [**threads.c**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q2-4.22/threads.c)
```
    worker_threads[0]=pthread_create(&t1,NULL,&thread_average,NULL);
	
    worker_threads[1]=pthread_create(&t2,NULL,&thread_minimum,NULL);
	
    worker_threads[2]=pthread_create(&t3,NULL,&thread_maximum,NULL);
```

Here in the above 3 **pthread_create()** statements:

  1. First argument is a pointer to pthread_t type that is the data type for threads as per "pthreads.h" library which have already been defined as t1, t2, t3 respectively.
  2. Second argument is attr pointing to a pthread_attr_t structure whose contents are used at thread creation time to determine attributes for the new thread. This structure is initialized using pthread_attr_init() function.In the above case attr is given as NULL, as we want the thread is created with default attributes.
  3. Third argument is a pointer to the start_routine of a thread that is the function invoked on the thread creation. In our case the functions invoked are *thread_average*, *thread_minimum*, *thread_maximum* respectively.
  4. Fourth Argument is *the sole* argument passed to start_routine() when invoked during thread creation. In our case it is NULL i.e. no arg is passed to our start_routine.
