#include <stdio.h>
#include <math.h>

double trade_price(double p, int n){
	return p*n;
}

main(){
	int i = 3;
	int *iptr;
	iptr = &i;

	printf("*iptr is %i. \n", *iptr);
	printf("*i is %i. \n", i);
	printf("location &i is %i. \n", &i);
	printf("iptr is %i. \n", iptr);
}