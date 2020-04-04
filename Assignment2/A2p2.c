#include <stdio.h>
// Commands to compile and run this code
// gcc A2p2.c -o A2p2
// ./A2p2

int main()
{
	int i =0;
	while(i < 5)
	{
		printf("Hello World\n");
		i++;
	}

	for(int i = 0; i < 5; i++)
	{
		printf("Hello World\n");
	}

	i=0;
	do
	{
		printf("Hello World\n");
		i++;
	}while(i<5);

	return 0;
}
