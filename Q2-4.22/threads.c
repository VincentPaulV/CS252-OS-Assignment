/*  Credits:
https://gist.github.com/Jabiribn/e58bf13c678953891900e5f982b48037
*/

/*  Header Files    */
#include<stdio.h>
#include<time.h>
//Header File to use threads in POSIX Based Systems
#include<pthread.h>

/*  Global Variables    */
#define MAX_COUNT 100
float array[MAX_COUNT];
int element_count;

/*  The Average, Minimum, Maximum Values: */
float average;
float minimum;
float maximum;

/*  Input Function  */
void input()
{
    int i;
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
    int i;
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
    int i;
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
    int i;
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

int main()
{
    input();

    int n,i;
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;

	n=pthread_create(&t1,NULL,&thread_average,NULL);
	pthread_join(t1,NULL);
	
    n=pthread_create(&t2,NULL,&thread_minimum,NULL);
    pthread_join(t2,NULL);
	
    n=pthread_create(&t3,NULL,&thread_maximum,NULL);
    pthread_join(t3,NULL);
}



