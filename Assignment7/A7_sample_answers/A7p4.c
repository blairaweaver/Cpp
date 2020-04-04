//to compile: gcc A7p4.c -lpthread -fpermissive -w -o A7p4
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <pthread.h>

int gnum_threads;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
int gcount[3]={0};//gcount[0] will store the number of integers from 1-60 whose Collatz list has length l<=5;
//gcount[1] will store the number of integers from 1-60 whose Collatz list has length l satisfying 5<l<10;
//gcount[2] will store the number of integers from 1-60 whose Collatz list has length l satisfying l>=10.
void usage(char *s)
{
	fprintf(stderr,"usage: %s <num_of_threads>\n",s);
	exit(0);
}

void *thread_function( void *arg )
{
	int index,i;//index will become 0,1,...,gnum_threads-1
	index = (int)(long)arg;//we may need "-fpermissive" when compiling to avoid possible warnings or errors.
	int count[3];//count[0] will store the number of integers from (index*60)/gnum_threads+1 to ((index+1)*60)/gnum_threads whose Collatz list has length l<=5;
	//count[1] will store the number of integers from (index*60)/gnum_threads+1 to ((index+1)*60)/gnum_threads whose Collatz list has length l satisfying 5<l<10;
	//count[2] will store the number of integers from (index*60)/gnum_threads+1 to ((index+1)*60)/gnum_threads whose Collatz list has length l satisfying l>=10.
	for(i=0;i<3;i++) count[i]=0;
	for(i=(index*60)/gnum_threads+1;i<=((index+1)*60)/gnum_threads;i++)//each thread processes a subset (60/gnum_threads) of integers
	{
		int t=i,y=1;//y will store the Collatz list length for i
		while(t!=1) 
		{
			if(t%2)
				t=3*t+1;
			else
				t=t/2;
			y++;
		}
		if(y<=5) count[0]++;
		else if(y<10) count[1]++;
		else count[2]++;
	}//for
	pthread_mutex_lock(&count_mutex);//updating gcount now; use mutex to avoid race condition
	for(i=0;i<3;i++) gcount[i]+=count[i];
	pthread_mutex_unlock(&count_mutex);
}//thread_function

int main(int argc, char *argv[])
{
	if(argc!=2) usage(argv[0]);
	gnum_threads=atoi(argv[1]);
	assert(gnum_threads>=2 && gnum_threads<=6);
	printf("using %d threads.\n",gnum_threads);
	
	pthread_t *thread;
	thread=(pthread_t*)malloc(gnum_threads*sizeof(pthread_t));
	if(thread==NULL) {fprintf(stderr,"out of memory\n");exit(-1);}
	
	int i,tmp;
	for ( i=0; i<gnum_threads; i++ )
	{
		tmp = pthread_create( &thread[i], NULL, thread_function, (void *)i );
		if ( tmp != 0 )
		{
			fprintf(stderr,"Creating thread %d failed\n", i);
			return 1;
		}
	}

	for ( i=0; i<gnum_threads; i++ )
	{
		tmp = pthread_join( thread[i], NULL );
		if ( tmp != 0 )
		{
			fprintf(stderr,"Joining thread %d failed\n", i);
			return 1;
		}
	}
	//for(i=0;i<3;i++) printf("gcount[%d]=%d\n",i,gcount[i]);
	printf("the number of integers from 1-60 whose Collatz list has length <=5 is %d\n",gcount[0]);
	printf("the number of integers from 1-60 whose Collatz list has length between 5 and 10 exclusive is %d\n",gcount[1]);
	printf("the number of integers from 1-60 whose Collatz list has length >=10 is %d\n",gcount[2]);
	free(thread);
	return 0;
}//main