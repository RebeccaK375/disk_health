#include <stdio.h>
#include <math.h>

double trade_price(double p, int n){
	return p*n;
}

main(){
	double price;
	int number;
	while (2 == scanf("%lf%i", &price, &number))
		printf("The total price of the trade is %f.\n",
			trade_price (price, number));
}