#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;
	while (scanf("%d",&i)==1)
	{
		printf("%d\t",i*i);
	}
	printf("\n");
	return 0;
}