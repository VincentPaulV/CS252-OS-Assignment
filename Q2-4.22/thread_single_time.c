/*  Credits:
https://gist.github.com/Jabiribn/e58bf13c678953891900e5f982b48037
*/

#include <stdio.h> 
#include <sys/time.h>
#include <stdlib.h>
#include<pthread.h>

/*  Global Variables    */
#define MAX_COUNT 5000000
float array[MAX_COUNT];
int element_count;
long long int i;

/*  The Average, Minimum, Maximum Values: */
float average;
float minimum;
float maximum;

/*  Input Function  */
void input()
{
    for(i=0;i<MAX_COUNT;i++)
    {
        array[i] = i;
    }
}

/*  Thread-1    */
void thread_average()
{
    float sum=0;
    for(i=0;i<MAX_COUNT;i++)
    {
        sum  = sum + array[i];
    }
    average = sum / MAX_COUNT ;
    printf("\nThe average value is %f",average);
}

/*  Thread-2    */
void thread_minimum()
{
    float temp;
    temp = array[0];
    for(i=0;i<MAX_COUNT;i++)
    {
        if(array[i]<temp)
        {
            temp = array[i];
        }
    }
    minimum = temp;
    printf("\nThe minimum value is %f",minimum);
}

/*  Thread-3    */
void thread_maximum()
{
    float temp;
    temp = array[0];
    for(i=0;i<MAX_COUNT;i++)
    {
        if(array[i]>temp)
        {
            temp = array[i];
        }
    }
    maximum = temp;
    printf("\nThe maximum value is %f",maximum);
}

int main()
{
    struct timeval TimeValue_Start;
    struct timezone TimeZone_Start; 
    struct timeval TimeValue_Final; 
    struct timezone TimeZone_Final; 
    long time_start, time_end; 
    double time_overhead;

    input();

    gettimeofday(&TimeValue_Start, &TimeZone_Start); 
    thread_average();
    thread_minimum();
    thread_maximum();

    gettimeofday(&TimeValue_Final, &TimeZone_Final);
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec; 
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec; 
    time_overhead = (time_end - time_start)/1000000.0;
    printf("\n\n\tTime in Seconds (T) : %lf\n",time_overhead);
}



