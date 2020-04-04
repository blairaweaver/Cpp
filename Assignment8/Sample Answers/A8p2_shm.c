//Link with -lrt
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
	const int SIZE = 4096;//shared memory region's size: large enough to hold 4 integers
	const char *name = "CSCI3232";//shared memory region's name
	pid_t pid;
	int shm_fd;
	void *ptr;

	pid = fork();/* fork a child process */
	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}
	else if (pid > 0) {  /* parent process: consumer */
		wait(NULL);//wait for child to finish since child is the producer
		/* open the shared memory segment */
		shm_fd = shm_open(name, O_RDONLY, 0666);
		if (shm_fd == -1) {
			fprintf(stderr,"shared memory failed in parent\n");
			exit(-1);
		}

		/* map the shared memory segment in the address space of the process */
		ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
		if (ptr == MAP_FAILED) {
			fprintf(stderr,"Map failed in parent\n");
			exit(-1);
		}

		/* now read from the shared memory region the array of four integers */
		int *p=(int *)ptr;//perform a cast because it is agreed upon that integers are stored in shared memory region
		printf("parent read the coordinates of two points: A(%d,%d) and B(%d,%d)\n\n",p[0],p[1],p[2],p[3]);
		int dx,dy,d;
		dx=(p[0]>p[2])?(p[0]-p[2]):(p[2]-p[0]);
		dy=(p[1]>p[3])?(p[1]-p[3]):(p[3]-p[1]);
		d=dx+dy;
		printf("The Manhattan distance between the two points is %d+%d=%d\n",dx,dy,d);

		/* remove the shared memory segment */
		if (shm_unlink(name) == -1) {
			fprintf(stderr,"Error removing %s\n",name);
			exit(-1);
		}
	}
	else { /* child process: producer */
		/* create the shared memory segment */
		shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
		if (shm_fd == -1) {
			fprintf(stderr,"shared memory failed in child\n");
			exit(-1);
		}
		/* configure the size of the shared memory segment */
		ftruncate(shm_fd,SIZE);
		/* map the shared memory segment in the address space of the process */
		ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
		if (ptr == MAP_FAILED) {
			fprintf(stderr,"Map failed in child\n");
			return -1;
		}

		int i,writenum[4];
		srand((unsigned)time(NULL));
		for(i=0;i<4;i++)
			writenum[i]=rand()%100;
		//write to the shared memory region. //you may check memset(), memcpy(), and memmove() in C
		memcpy(ptr,writenum,sizeof(writenum));//copy sizeof(writenum) bytes from writenum to ptr

		printf("child wrote the coordinates of two points: A(%d,%d) and B(%d,%d)\n\n", writenum[0], writenum[1],writenum[2], writenum[3]);
	}

	return 0;
}
