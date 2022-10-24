/*  Credits:
https://gist.github.com/Jabiribn/e58bf13c678953891900e5f982b48037
*/

#include <stdio.h> 
#include <sys/time.h>
#include <stdlib.h>
#include<pthread.h>

/*  Global Variables    */
#define MAX_COUNT 500000
float array[MAX_COUNT];
int element_count;
long long int i;
int worker_threads[3];

/*  The Average, Minimum, Maximum Values: */
float average;
float minimum;
float maximum;

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

/*  Thread-1    */
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

/*  Thread-2    */
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

/*  Thread-3    */
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

int main(void)
{
    struct timeval TimeValue_Start;
    struct timezone TimeZone_Start; 
    struct timeval TimeValue_Final; 
    struct timezone TimeZone_Final; 
    long time_start, time_end; 
    double time_overhead;
    input();
    int i;
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    gettimeofday(&TimeValue_Start, &TimeZone_Start);

	worker_threads[0]=pthread_create(&t1,NULL,&thread_average,NULL);
	//pthread_join(t1,NULL);
	
    worker_threads[1]=pthread_create(&t2,NULL,&thread_minimum,NULL);
    //pthread_join(t2,NULL);
	
    worker_threads[2]=pthread_create(&t3,NULL,&thread_maximum,NULL);
    //pthread_join(t3,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

    gettimeofday(&TimeValue_Final, &TimeZone_Final);
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec; 
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec; 
    time_overhead = (time_end - time_start)/1000000.0;
    printf("\n\n\tTime in Seconds (T) : %lf\n",time_overhead);
}
