#include <stdio.h> 
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
    input();
    
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    
    worker_threads[0]=pthread_create(&t1,NULL,&thread_average,NULL);
	
    worker_threads[1]=pthread_create(&t2,NULL,&thread_minimum,NULL);
	
    worker_threads[2]=pthread_create(&t3,NULL,&thread_maximum,NULL);

    pthread_join(t1,NULL);

    pthread_join(t2,NULL);

    pthread_join(t3,NULL);
}
