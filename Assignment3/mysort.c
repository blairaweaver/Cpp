#include "mysort.h"
#include <stdlib.h>
#include <stdio.h>

void generateNums(int *myarr, int len){
	srand(time(0));
	for(int i = 0; i < len; i++) {
		int t = rand();
		int ran = rand() % 101;
		*(myarr+i) = ran;
	}
}

void sortNums(int *myarr, int len){
	for(int i = 0; i < len; i++){
		int min = *(myarr+i);
		int loc = i;
		for(int j = i; j < len; j++){
			if(*(myarr+j) < min){
				min = *(myarr+j);
				loc = j;
			}
		}
		int temp = min;
		*(myarr+loc) = *(myarr+i);
		*(myarr+i) = temp;
	}
}
