#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	if(argc!=2) {fprintf(stderr,"usage: %s <string>\n",argv[0]);exit(0);}
	pid_t pid;

	/* fork a child process */
	pid = fork();

	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}
	else if (pid == 0) { /* child process */
		printf("I am the child. Printing the lower case version:\n");
		int i;
		for(i=0;argv[1][i]!='\0';i++)
			printf("%c",tolower(argv[1][i]));
		printf("\n");
	}
	else { /* parent process */
		wait(NULL);//wait for the child process to finish to avoid printing chaos
		printf("I am the parent. Printing the reversed upper case version:\n");
		int i;
		for(i=0;argv[1][i]!='\0';i++) ;
		for(i--;i>=0;i--)
			printf("%c",toupper(argv[1][i]));
		printf("\n");
	}
    
    return 0;
}
