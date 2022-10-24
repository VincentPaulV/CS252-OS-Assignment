# 4.22 Writing a Multi-Threaded Program

## Question:

Write a multithreaded program that calculates various statistical values for a list of numbers. 
This program will be passed a series of numbers on the command line and will then create three separate worker threads. 
One thread will determine the **average** of the numbers, the second will determine the **maximum** value, and the third will determine the **minimum ** value. 
For example, suppose your program is passed the integers 90 81 78 95 79 72 85 

The program will report
>         The average value is 82
>         The minimum value is 72
>         The maximum value is 95

The variables representing the average, minimum, and maximum values will be stored globally. 
The worker threads will set these values, and the parent thread will output the values once the workers have exited. 
(We could obviously expand this program by creating additional threads that determine other statistical values, such as median and standard deviation).

## Approach:
### The C Program: [**threads.c**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q2-4.22/threads.c)
Global Variables:
As mentioned in the question we have to globally define average, minimum, and maximum values
```
/*  The Average, Minimum, Maximum Values: */
float average;
float minimum;
float maximum;
```
The other global variables
```
/*  Global Variables    */
#define MAX_COUNT 500000
float array[MAX_COUNT];
int element_count;
long long int i;
int worker_threads[3];
```
MAX_COUNT is the maximum size of array.
element_count is the number of elements user wants to enter.
i is the common looping variable globalized for convienience.
worker_threads[3] is an array storing the returned values of pthread_create()

Input function:

```
/*  Input Function  */
void input()
{
    printf("Enter element count: ");
    scanf("%d",&element_count);
    for(i=0;i<element_count;i++)
    {
        scanf("%f",&array[i]);
    }
}
```

We define 3 functions for start_routine namely *thread_average*, *thread_minimum*, *thread_maximum* as below:

```
void *thread_average()
{
    float sum=0;
    for(i=0;i<element_count;i++)
    {
        sum  = sum + array[i];
    }
    average = sum / element_count ;
    printf("\nThe average value is %f",average);
}
```

```
void *thread_minimum()
{
    float temp;
    temp = array[0];
    for(i=0;i<element_count;i++)
    {
        if(array[i]<temp)
        {
            temp = array[i];
        }
    }
    minimum = temp;
    printf("\nThe minimum value is %f",minimum);
}
```

```
void *thread_maximum()
{
    float temp;
    temp = array[0];
    for(i=0;i<element_count;i++)
    {
        if(array[i]>temp)
        {
            temp = array[i];
        }
    }
    maximum = temp;
    printf("\nThe maximum value is %f",maximum);
}
```


## List of Data Types & Functions involved in thread-making:
### **1. Data Type *pthread_t:***
Line 88-90 in [**threads.c**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q2-4.22/threads.c)
```
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
```

pthread_t is the data type for thread.


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
  5. On success, these functions return 0; on error, they return a nonzero error number.

### **3. Function *pthread_join():***
```
int pthread_join(pthread_t thread, void **retval);
```
Lines 100-104 in [**threads.c**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q2-4.22/threads.c)
```
    pthread_join(t1,NULL);

    pthread_join(t2,NULL);

    pthread_join(t3,NULL);
```
Here in the above 3 **pthread_join()** statements:

  1. The pthread_join() function waits for the thread specified by thread to terminate.  If that thread has already terminated, then pthread_join() returns immediately.The thread specified by thread must be joinable.
  2. First argument is a pthread_t type that is the data type for threads as per "pthreads.h" library which have already been defined as t1, t2, t3 respectively.
  3. Second argument is retval that is if not NULL then it has the exit status of thread when pthread_exit() was called. In our case we haven't called pthread_exit() prior to pthread_join() hence we give argument as NULL.

## Analysis of Time:
### Description of Files:
1. [**threads_time.c**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q2-4.22/threads_time.c) on compilation gives [**thread_time**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q2-4.22/thread_time) and contains the time-based checking for MAX_COUNT=5000000 elements.
```
vince@MacBook-Pro-2 Q2-4.22 % gcc -o thread_time threads_time.c -lm -pthread
threads_time.c:43:1: warning: non-void function does not return a value [-Wreturn-type]
}
^
threads_time.c:59:1: warning: non-void function does not return a value [-Wreturn-type]
}
^
threads_time.c:75:1: warning: non-void function does not return a value [-Wreturn-type]
}
^
3 warnings generated.
vince@MacBook-Pro-2 Q2-4.22 % ./thread_time

The minimum value is 0.000000
The average value is 2228030.750000
The maximum value is 4999999.000000

        Time in Seconds (T) : 0.023717
```

2. [**thread_single_time.c**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q2-4.22/thread_single_time.c) on compilation gives [**sthread_time**](https://github.com/VincentPaulV/CS252-OS-Assignment/blob/main/Q2-4.22/sthread_time) and contains the time-based checking for MAX_COUNT=5000000 elements.
```
vince@MacBook-Pro-2 Q2-4.22 % gcc -o thread_time threads_time.c -lm -pthread
vince@MacBook-Pro-2 Q2-4.22 % gcc -o sthread_time thread_single_time.c -lm -pthread
vince@MacBook-Pro-2 Q2-4.22 % ./sthread_time

The average value is 2496735.250000
The minimum value is 0.000000
The maximum value is 4999999.000000

        Time in Seconds (T) : 0.051739
```

As we can observe here for 5000000 elements(taken to increase the computation time over the thread overhead so that we can emphasize over the thread efficiency) for:

**Single Thread:**
```
Time in Seconds (T) : 0.051739
```

**Multi Thread:**
```
Time in Seconds (T) : 0.023717
```
Multi-Threading works **0.028022 seconds faster** than Single Threaded Program.


