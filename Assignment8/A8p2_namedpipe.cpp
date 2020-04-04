//This program demonstrates the usage of named pipe between two related processes (parent and child).
//The pipe is only used as a unidirectional pipe.
//See also named_pipe2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <ctime>
#include <iostream>

using namespace std;


#define MAX 10
void child(char *path)
{
	int fd;
	ssize_t num;
	int arr[MAX];

	fd = open(path, O_RDONLY);
	if(fd==-1) {fprintf(stderr,"in child, open error=%d, msg=%s\n",errno,strerror(errno)); exit(-1);}

	read(fd, arr, sizeof(arr));//writer will not start to write until reader has opened the named pipe; use "man 7 fifo" for more information
	printf("child received the coordinates of two points: A(%d,%d) and B(%d,%d)\n",arr[0], arr[1], arr[2], arr[3]);
		
	int a1 = abs(arr[0] - arr[2]);
	int a2 = abs(arr[1] - arr[3]);
		
	printf("The Manhattan distance between the two points is %d+%d=%d\n", a1, a2, a1+a2);
	close(fd);
}//child
 
void parent(char *path)
{
	int fd;
	ssize_t num;
	
	int random[4];
	srand((unsigned)time(NULL));
	for(int i = 0; i < 4; i++){
		random[i] = rand() % 100;
	}
	printf("parent sent the coordinates of two points: A(%d,%d) and B(%d,%d)\n",random[0],random[1],random[2],random[3]);

	fd = open(path, O_WRONLY);
	if(fd==-1) {fprintf(stderr,"in parent, open error=%d,msg=%s\n",errno,strerror(errno)); exit(-1);}

	write(fd, random, sizeof(random));
	
	
	close(fd);
	unlink(path);
}//parent
 
int main()
{
	//char *path = "/tmp/fifo";
	char path[1024];//used to store the absolute path of the file backing our named pipe
	if (getcwd(path, sizeof(path)) == NULL)
	{
		perror("getcwd() error");
		exit(0);
	}
	strcat(path,"/fifoTest");//now path may contain a string that looks like /home/student/Desktop/fifoTest
	pid_t pid;

	//set buffering method for file stream "stdout": characters are saved up until a newline is output
	setlinebuf(stdout);//see http://linux.die.net/man/3/setlinebuf
	//remove a link to a file
	unlink(path);//see http://linux.die.net/man/3/unlink
	//makes a FIFO special file (a named pipe) with name 'path'. 
	int r=mkfifo(path, 0600);//see http://linux.die.net/man/3/mkfifo or use "man 3 mkfifo" in Linux
	if(r==-1) {fprintf(stderr,"in main, mkfifo call error=%d, msg=%s\n",errno,strerror(errno)); exit(-1);}

	pid = fork();
	if(pid<0) {fprintf(stderr,"in main, fork call error=%d, msg=%s\n",errno,strerror(errno)); exit(-1);}
	else if (pid == 0) {
		child(path);//child process is the writing end
	} else {
		parent(path);//parent process is the reading end
	}
	//unlink(path);
	return 0;
}//main
