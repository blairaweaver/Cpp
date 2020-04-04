//to compile: g++ A6p4.cpp -lpthread -o A6p4
//or try: g++ A6p4.cpp -lpthread -fpermissive -o A6p4
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <pthread.h>
#include <iostream>

using namespace std;

int arr[5][12];
int gnum_threads;//number of threads to perform the update task

void usage(char *s)
{
	fprintf(stderr,"usage: %s <num_of_threads>\n",s);
	exit(0);
}//usage

void *thread_function( void *arg )
{
	int index,i,j;//index will become 0,1,...,gnum_threads-1

	index = (int)(long)arg;//we may need "-fpermissive" when compiling; otherwise "loses precision" error might occur because sizeof(int) possibly has a smaller value than sizeof(void *).

	for(i=0;i<5;i++)//each thread updates a portion of the array by choosing selected columns of the array according to its own index
		for(j=(index*12)/gnum_threads;j<(index+1)*12/gnum_threads;j++)
			arr[i][j]*=arr[i][j];//square the element
	//no return is necessary for our purpose; you can also write "return NULL;"
}//thread_function

void generateIntegers()
{
	srand(time(NULL));//seed so that we may obtain different random integers on different runs
	int i,j;
	for(i=0;i<5;i++)
		for(j=0;j<12;j++)
			arr[i][j]=(rand()%49)+1;//a random integer in the range of 1,2,...,49
}

void PrintIntegers()
{
	int i,j;
	for(i=0;i<5;i++)
	{
		for(j=0;j<12;j++)
			std::cout<<arr[i][j]<<"\t";
		std::cout<<endl;
	}
}

int main(int argc, char *argv[])
{
	if(argc!=2) usage(argv[0]);
	gnum_threads=atoi(argv[1]);
	assert(gnum_threads>=2 && gnum_threads<=4);
	printf("using %d threads.\n",gnum_threads);
	
	pthread_t *thread;
	thread=new pthread_t [gnum_threads];
	if(thread==NULL) {std::cerr<<"out of memory\n";exit(-1);}
	
	generateIntegers();
	printf("original array:\n");
	PrintIntegers();
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
	printf("updated array:\n");
	PrintIntegers();//the printing task is not required to be evenly divided; in fact, you should not put printing code in the thread function
	delete [] thread;//good practice to deallocate dynamic storage
	return 0;
}//main