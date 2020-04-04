#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

using namespace std;


int main(int argc, char *argv[])
{
	char * a;
	a = argv[1]; 
	pid_t pid;
	char c;
	int i = 0;

	pid = fork();
	if(pid<0) {fprintf(stderr,"fork failed\n"); exit(pid);}
	else if (pid == 0) { /* child process */
		printf ("I am the child. Printing the lowercase version: \n");
		while (a[i]){
			c = a[i];
			putchar (tolower(c));
			i++;
		}
		cout << endl;
		return 0;
	}
	else if (pid > 0) { /* parent process */
		wait(NULL);//wait for child process to finish
		printf ("I am the parent. Printing the reversed uppercase version: \n");
		for(int i = strlen(a) - 1; i >= 0; i--){
			c = a[i];
			putchar (toupper(c));
		}
		cout << endl;
		return 0;
	}
}
