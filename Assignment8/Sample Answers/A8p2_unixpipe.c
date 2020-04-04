#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define READ_END	0
#define WRITE_END	1

int main()
{
	pid_t pid;
	int fd[2];

	if (pipe(fd) == -1) {/* create the pipe */
		fprintf(stderr,"Pipe failed");
		return 1;
	}

	pid = fork();/* fork a child process */
	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}
	else if (pid > 0) {  /* parent process to be used as sender */
		/* close the unused end of the pipe */
		close(fd[READ_END]);

		int i,writenum[4];
		srand((unsigned)time(NULL));
		for(i=0;i<4;i++)
			writenum[i]=rand()%100;
		/* write to the pipe */
		if(write(fd[WRITE_END], writenum, sizeof(writenum))==-1)//write sizeof(writenum) bytes from writenum to the write end of the pipe
			fprintf(stderr, "write error");
		printf("parent sent the coordinates of two points: A(%d,%d) and B(%d,%d)\n\n", writenum[0], writenum[1],writenum[2], writenum[3]);

		/* close the write end of the pipe */
		close(fd[WRITE_END]);
	}
	else { /* child process to be used as receiver */
		/* close the unused end of the pipe */
		close(fd[WRITE_END]);

		int readnum[4];
		/* read from the pipe */
		if(read(fd[READ_END], readnum, sizeof(readnum))==-1)
			fprintf(stderr, "read error");
		printf("child received the coordinates of two points: A(%d,%d) and B(%d,%d)\n\n",readnum[0],readnum[1],readnum[2],readnum[3]);
		int dx,dy,d;
		dx=(readnum[0]>readnum[2])?(readnum[0]-readnum[2]):(readnum[2]-readnum[0]);
		dy=(readnum[1]>readnum[3])?(readnum[1]-readnum[3]):(readnum[3]-readnum[1]);
		d=dx+dy;
		printf("The Manhattan distance between the two points is %d+%d=%d\n",dx,dy,d);

		/* close the write end of the pipe */
		close(fd[READ_END]);
	}

	return 0;
}
