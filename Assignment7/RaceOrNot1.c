#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t count_mutex3 = PTHREAD_MUTEX_INITIALIZER;
int c[2] = {0,0};

void *UpdateC1(void *arg)
{
	int i;
	for(i=0;i<1000000;i++)
	{
		pthread_mutex_lock(&count_mutex);
		c[0]=(c[0]+1)%2;
		c[1]=(c[1]+1)%2;
		pthread_mutex_unlock(&count_mutex);
	}
	return NULL;
}

void *UpdateC2(void *arg)
{
	int i;
	for(i=0;i<1000000;i++)
	{
		pthread_mutex_lock(&count_mutex);
		c[0]=(c[0]+1)%2;
		c[1]=(c[1]+1)%2;
		pthread_mutex_unlock(&count_mutex);
	}
	return NULL;
}

void *UpdateC3(void *arg)
{
	int i;
	for(i=0;i<1000000;i++)
	{
		pthread_mutex_lock(&count_mutex3);
		c[0]=(c[0]+1)%2;
		c[1]=(c[1]+1)%2;
		pthread_mutex_unlock(&count_mutex3);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	int rt,i;
	pthread_t t[3]; 

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