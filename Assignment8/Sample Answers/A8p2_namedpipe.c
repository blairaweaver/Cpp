#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
 
void child(char *path)
{
	int fd;

	fd = open(path, O_WRONLY);//O_WRONLY effectively makes the pipe unidirectional
	if(fd==-1) {fprintf(stderr,"in child, open error=%d, msg=%s\n",errno,strerror(errno)); exit(-1);}
	int i,writenum[4];
	srand((unsigned)time(NULL));
	for(i=0;i<4;i++)
		writenum[i]=rand()%100;
	/* write to the pipe */
	if(write(fd, writenum, sizeof(writenum))==-1)//write sizeof(writenum) bytes from writenum to the write end of the pipe
		fprintf(stderr, "write error");
	printf("parent sent the coordinates of two points: A(%d,%d) and B(%d,%d)\n\n", writenum[0], writenum[1],writenum[2], writenum[3]);

	close(fd);
}//child
 
void parent(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);//O_RDONLY effectively makes the pipe unidirectional
	if(fd==-1) {fprintf(stderr,"in parent, open error=%d,msg=%s\n",errno,strerror(errno)); exit(-1);}
	int readnum[4];
	/* read from the pipe */
	if(read(fd, readnum, sizeof(readnum))==-1)
		fprintf(stderr, "read error");
	printf("child received the coordinates of two points: A(%d,%d) and B(%d,%d)\n\n",readnum[0],readnum[1],readnum[2],readnum[3]);
	int dx,dy,d;
	dx=(readnum[0]>readnum[2])?(readnum[0]-readnum[2]):(readnum[2]-readnum[0]);
	dy=(readnum[1]>readnum[3])?(readnum[1]-readnum[3]):(readnum[3]-readnum[1]);
	d=dx+dy;
	printf("The Manhattan distance between the two points is %d+%d=%d\n",dx,dy,d);

	close(fd);
	unlink(path);//after message is read and pipe fd is closed, we are safe to remove the named pipe
}//parent
 
int main()
{
	char path[1024];//used to store the absolute path of the file backing our named pipe
	if (getcwd(path, sizeof(path)) == NULL)
	{
		perror("getcwd() error");
		exit(0);
	}
	strcat(path,"/A8p2_namedpipe");//now path may contain a string that looks like /home/student/Desktop/A8p2_namedpipe
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

	return 0;
}//main
