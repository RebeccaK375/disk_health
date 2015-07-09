#include <stdio.h>
#include <math.h>

double doubling_time(double r){
	double result = log(2.0)/log(1.0 + r/100.0);
	return result;
}

main () {
	printf("Your money doubles in about %f years at %f percent.\n", doubling_time(4.0), 4.0);
}