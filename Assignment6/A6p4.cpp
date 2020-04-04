#include <iostream>
#include <bits/stdc++.h>
#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
using namespace std;

const int MAX = 12;
int part = 0;

struct arg_struct {
        int arg1;
	int arg2[5][12];
};

void randomArray(int x[][12]) {
	for (int i =0; i < 5; i++){
		for (int j =0; j < 12; j++) {
			*((*(x+i))+j) = rand() % 49 + 1;
		}
	}

}

void printArray(int x[][12]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 12; j++) {
			cout << *((*(x+i))+j) << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
}

void* squared(void* arg) {
	struct arg_struct *args = (struct arg_struct *) arg;
	int thread_part = part++;
	for (int i = 0; i < 5; i++) {
		for (int j = thread_part * (MAX / args->arg1); j < (thread_part +1) * (MAX / args ->arg1); j++) {
			*((*(args->arg2+i))+j) *= *((*(args->arg2 + i)) +j);
		}
	}
}

int main (int argc, char* argv[]) {
        int x = atoi (argv[1]);
        srand(time(NULL));
        struct arg_struct args;
        args.arg1 = x;
	randomArray(args.arg2);
	cout << "Original Array\n";
	printArray(args.arg2);

        pthread_t threads[x];
        for (int i = 0; i < x; i++)
                pthread_create(&threads[i], NULL, squared, &args);
        for (int i = 0; i < x; i++)
                pthread_join(threads[i], NULL);
	cout << "Modified Array\n";
	printArray(args.arg2);
        return 0;
}
