#include <iostream>
#include <bits/stdc++.h>
#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <semaphore.h>
#include <errno.h>
using namespace std;

sem_t s1;
//a if less than 5, b is for 5-10, and c is >10
int a=0,b=0,c=0;
int gnum_threads;

void usage(char *s)
{
	fprintf(stderr,"usage: %s <num_of_threads>\n",s);
	exit(0);
}

void* thread_func(void* arg) {
	int count = 1;
	int index = (int) (long) arg;
	for(int i=(index*60)/gnum_threads;i<(index+1)*60/gnum_threads;i++){
		int var = i + 1;
		while(var!=1) {
        		if(var%2==0)
            			var = var/2;
        		else
            			var = 3*var+1;
        		count++;
		}
		sem_wait(&s1);
		if(count <= 5)
			a++;
		else if(count >= 10)
			c++;
		else
			b++;
		sem_post(&s1);
		count = 1;
	}
	
	
}

int main (int argc, char* argv[]) {
    if(argc!=2) usage(argv[0]);
	gnum_threads=atoi(argv[1]);
	assert(gnum_threads>=2 && gnum_threads<=6);
	printf("using %d threads.\n",gnum_threads);
	
	pthread_t *thread;
	thread=new pthread_t [gnum_threads];
	if(thread==NULL) {std::cerr<<"out of memory\n";exit(-1);}
	
	sem_init(&s1, 0, 1);


    for (int i = 0; i < gnum_threads; i++)
        pthread_create(&thread[i], NULL, thread_func, (void *)i);
    for (int i = 0; i < gnum_threads; i++)
         pthread_join(thread[i], NULL);

    cout << "The number of integers from 1-60 whose Collatz list has length <=5 is " << a << "\n";
    cout << "The number of integers from 1-60 whose Collatz list has length between 5 and 10 exclusive is " << b << "\n";
    cout << "The number of integers from 1-60 whose Collatz list has length >=10 is " << c << "\n";

	
    return 0;
}
