//to compile: gcc TestAssert.c -o TestAssert
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
	int i;
	printf("enter an integer at least 10: ");
	scanf("%d",&i);
	assert(i>=10);
	printf("You entered: %d\n",i);
	return 0;
}
