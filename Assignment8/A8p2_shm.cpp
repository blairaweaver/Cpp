#include "protocol.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <ctime>
int main() {
	pid_t pid;
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}
	else if (pid > 0) {
  int fd = shm_open(NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
  if (fd < 0) {
    perror("shm_open()");
    return EXIT_FAILURE;
  }

  ftruncate(fd, SIZE);

  int *data =
      (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  srand((unsigned)time(NULL));
		for(int i = 0; i < 4; i++){
			data[i] = rand() % 100;
		}
printf("parent sent the coordinates of two points: A(%d,%d) and B(%d,%d)\n",data[0],data[1],data[2],data[3]);
  munmap(data, SIZE);

  close(fd);

  return EXIT_SUCCESS;
	}
	else { /* child process: producer */
	  int fd = shm_open(NAME, O_RDONLY, 0666);
  if (fd < 0) {
    perror("shm_open()");
    return EXIT_FAILURE;
  }

  int *data =
      (int *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);

  printf("child received the coordinates of two points: A(%d,%d) and B(%d,%d)\n",data[0], data[1], data[2], data[3]);
		
		int a1 = abs(data[0] - data[2]);
		int a2 = abs(data[1] - data[3]);
		
		printf("The Manhattan distance between the two points is %d+%d=%d\n", a1, a2, a1+a2);

  munmap(data, SIZE);

  close(fd);

  shm_unlink(NAME);

  return EXIT_SUCCESS;
	}
}