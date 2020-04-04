#include <stdio.h>

int main()
{
	for(int i = 65; i < 91; i++)
	{
		printf("%c\t ASCII value:%d\n",(char) i, i);
	}

	for(int i =97; i < 123; i++)
	{
		printf("%c\t ASCII value:%d\n",(char) i, i);
	}
	for(int i = 48; i < 58; i++)
	{
		printf("%c\t ASCII value:%d\n",(char) i, i);
	}

	return 0;
}
