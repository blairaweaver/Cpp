#include "mysort.h"

int main(int argc, char *argv[]) {
	int N = atoi(argv[1]);
	int myarr[N];
	int *p = myarr;
	int len = N;
	generateNums(p, len);
	for(int i =0; i < len; i++){
		printf("%d, ", *(p+i));
	}
	printf("\n");
	sortNums(p, len);
	for(int i =0; i < len; i++){
		printf("%d, ", *(p+i));
	}
	printf("\n");
	return 0;
}
