//This program demonstrates the usage of ordinary pipes, which is unidirectional
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctime>
#include <iostream>

using namespace std;


#define MAX 10

int main(void)
{
	
	pid_t pid;
	int fd[2];

	/* create the pipe */
	if (pipe(fd) == -1) {//you can type "man 2 pipe" inside Linux to get help for the function "pipe"; or visit http://linux.die.net/man/3/pipe
		fprintf(stderr,"Pipe failed");
		return 1;
	}

	pid = fork();/* now fork a child process */
	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}
	else if (pid > 0) {  /* parent process */
		int random[4];
		srand((unsigned)time(NULL));
		for(int i = 0; i < 4; i++){
			random[i] = rand() % 100;
		}
		printf("parent sent the coordinates of two points: A(%d,%d) and B(%d,%d)\n",random[0],random[1],random[2],random[3]);
		/* parent is used as a writer, so close the unused read end of the pipe */
		close(fd[0]);

		close(1);

		dup(fd[1]);
		write(1, random, sizeof(random));
		

		/* close the write end of the pipe */
		close(fd[1]);
	}
	else { /* child process */
		
		/* child is used as a reader, so close the unused write end of the pipe */
		close(0);
		close(fd[1]);
		

		dup(fd[0]);
		int arr[MAX];
		/* read from the read end of the pipe */
		

		int n = read(fd[0], arr, sizeof(arr)); 
		printf("child received the coordinates of two points: A(%d,%d) and B(%d,%d)\n",arr[0], arr[1], arr[2], arr[3]);
		
		int a1 = abs(arr[0] - arr[2]);
		int a2 = abs(arr[1] - arr[3]);
		
		printf("The Manhattan distance between the two points is %d+%d=%d\n", a1, a2, a1+a2);
		
		/* close the read end of the pipe */
		close(fd[0]);
	}

	return 0;
}
