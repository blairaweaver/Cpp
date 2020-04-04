//to compile: g++ A6p3.cpp -lpthread -o A6p3
//or try: g++ A6p3.cpp -lpthread -fpermissive -w -o A6p3
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <pthread.h>

char arr[61];//array to hold 60 characters and the terminating \0 character
int gnum_threads;//number of threads to perform the conversion task

void usage(char *s)
{
	fprintf(stderr,"usage: %s <num_of_threads>\n",s);
	exit(0);
}

void *thread_function(void *arg)
{
	int index,i;//index will become 0,1,...,gnum_threads-1

	index = (int)(long)arg;//we may need "-fpermissive" when compiling; otherwise "loses precision" error might occur because sizeof(int) possibly has a smaller value than sizeof(void *).
	for(i=(index*60)/gnum_threads;i<(index+1)*60/gnum_threads;i++)//each thread updates a portion of the string depending on its own index; notice the number of characters converted by each thread is (index+1)*60/gnum_threads-index*60/gnum_threads=60/gnum_threads
		arr[i]=tolower(arr[i]);
}

void generateString()
{
	srand(time(NULL));//seed so that we may obtain different random characters on different runs
	int i;
	for(i=0;i<60;i++) arr[i]=rand()%26+'A';//initialize with random upper case characters
	arr[60]='\0';//C string is \0 terminated; we do this for convenience of printing
}

int main(int argc, char *argv[])
{
	if(argc!=2) usage(argv[0]);
	gnum_threads=atoi(argv[1]);
	assert(gnum_threads>=2 && gnum_threads<=6);
	printf("using %d threads.\n",gnum_threads);
	
	pthread_t *thread;
	thread=new pthread_t [gnum_threads];
	if(thread==NULL) {fprintf(stderr,"out of memory\n");exit(-1);}
	
	generateString();
	printf("original upper case version:\n%s\n\n",arr);
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
	printf("lower case version:\n%s\n",arr);//the printing task is not required to be evenly divided; in fact, you should not put printing code in the thread function
	delete [] thread;//good practice to deallocate dynamic storage
	return 0;
}//main
