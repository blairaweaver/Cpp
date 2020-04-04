//to compile this program: gcc spareroot.c -lm -o spareroot
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double zeta(double s)
{
	const double precision = 1e-8;
	double value = 0.0;
	double term = 1.0;
	int d;
	
	for (d = 2; term > precision; ++d)
	{
		value += term;
		term = 1.0 / pow(d, s);
	}
	
	return value;
}//function zeta to compute Riemann's zeta function for input s>1

int main(int argc, char *argv[])
{
	double d,r;
	double d1,r1;
	printf("enter a number greater than 1: ");
	scanf("%lg",&d);
	if(d<=1)
	{
		fprintf(stderr,"your input should be greater than 1.\n");
		exit(0);
	}
	r=zeta(d);
	printf("zeta(%f)=%f\n",d,r);
	
	printf("enter a number greater than 1: ");
	scanf("%lg",&d1);
	if(d1<=1)
	{
		fprintf(stderr,"your input should be greater than 1.\n");
		exit(0);
	}
	r1=zeta(d1);
	printf("zeta(%f)=%f\n",d1,r1);

	return 0;
}
