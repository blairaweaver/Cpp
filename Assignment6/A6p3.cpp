#include <iostream>
#include <bits/stdc++.h>
#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
using namespace std;

const int MAX = 60;
int part = 0;

struct arg_struct {
	int arg1;
	string arg2;
};

string randomString() {
	char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	string ran = "";
	for (int i = 0; i < MAX; i++)
		ran = ran + alphabet[rand() % 26];
	return ran;
}

void* toUpper(void* arg) {
	struct arg_struct *args = (struct arg_struct *) arg;
	int thread_part = part++;

	for ( int i = thread_part * (MAX / args->arg1); i < (thread_part + 1) * (MAX /args->arg1); i++){
		args->arg2[i] =  tolower(args->arg2[i]);
	}
}

int main (int argc, char* argv[]) {
	int x = atoi (argv[1]);
	srand(time(NULL));
	string ran1 = randomString();
	cout << ran1 << "\n";
	struct arg_struct args;
	args.arg1 = x;
	args.arg2 = ran1;
	pthread_t threads[x];
	for (int i = 0; i < x; i++)
		pthread_create(&threads[i], NULL, toUpper, &args);
	for (int i = 0; i < x; i++)
		pthread_join(threads[i], NULL);
	cout << args.arg2 << "\n";
	return 0;
}
