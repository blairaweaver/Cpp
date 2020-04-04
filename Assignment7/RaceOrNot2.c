#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

sem_t s1;
int c[2] = {0,0};

void *UpdateC1(void *arg)
{
	int i;
	for(i=0;i<1000000;i++)
	{
		sem_wait(&s1);
		c[0]=(c[0]+1)%2;
		c[1]=(c[1]+1)%2;
		sem_post(&s1);
	}
	return NULL;
}

void *UpdateC2(void *arg)
{
	int i;
	for(i=0;i<1000000;i++)
	{
		sem_wait(&s1);
		c[0]=(c[0]+1)%2;
		c[1]=(c[1]+1)%2;
		sem_post(&s1);
	}
	return NULL;
}

void *UpdateC3(void *arg)
{
	int i;
	for(i=0;i<1000000;i++)
	{
		sem_wait(&s1);
		c[0]=(c[0]+1)%2;
		c[1]=(c[1]+1)%2;
		sem_post(&s1);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	int rt,i;
	pthread_t t[3]; 

	if(sem_init(&s1, 0, 2)==-1)//Initialize the semaphore;
	{
		fprintf(stderr,"sem_init failed. errno=%d\n",errno);
		exit(1);
	}
	rt=pthread_create( &t[0], NULL, &UpdateC1, NULL);
	if( rt!=0 )
		fprintf(stderr,"Thread %d creation failed: %d\n", 0,rt);
	rt=pthread_create( &t[1], NULL, &UpdateC2, NULL);
	if( rt!=0 )
		fprintf(stderr,"Thread %d creation failed: %d\n", 1,rt);
	rt=pthread_create( &t[2], NULL, &UpdateC3, NULL);
	if( rt!=0 )
		fprintf(stderr,"Thread %d creation failed: %d\n", 2,rt);

	for(i=0;i<3;i++)
	{
		rt=pthread_join( t[i], NULL);
		if( rt!=0 )
			fprintf(stderr,"Wait for thread %d failed: %d\n", i,rt);
	}

	printf ("\t%c\t%c\n",'a'+c[0],'a'+c[1]);
	return 0;
}