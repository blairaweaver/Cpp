#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

sem_t s1;
int c=0,x=0;

void *UpdateC1(void *arg)
{
	int i;
	for(i=0;i<2000000;i++)	{
		sem_wait(&s1);
		c++;	x++;
		sem_post(&s1);
	}
}

void *UpdateC2(void *arg)
{
	int i,x=0;
	for(i=0;i<4999999;i++)	{
		sem_wait(&s1);
		c++;	x++;
		sem_post(&s1);
	}
}

int main(int argc, char *argv[])
{
	int rt,i;
	pthread_t t[2]; 

	if(sem_init(&s1, 0, 1)==-1)//Initialize the semaphore;
	{
		fprintf(stderr,"sem_init failed. errno=%d\n",errno);
		exit(1);
	}
	rt=pthread_create( &t[0], NULL, UpdateC1, NULL);
	if( rt!=0 )
		fprintf(stderr,"Thread %d creation failed: %d\n", 0,rt);
	rt=pthread_create( &t[1], NULL, UpdateC2, NULL);
	if( rt!=0 )
		fprintf(stderr,"Thread %d creation failed: %d\n", 1,rt);

	for(i=0;i<2;i++)
	{
		rt=pthread_join(t[i], NULL);
		if( rt!=0 )
			fprintf(stderr,"Wait for thread %d failed: %d\n", i,rt);
	}

	printf ("\t%c\t%c\n",'a'+(c%2),'a'+(x%2));
	return 0;
}