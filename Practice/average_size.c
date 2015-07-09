#include <stdio.h>

main () {
	int average, size_one, size_two, size_three;
	printf ("Please type three trade sizes.\n");
	scanf("%i", &size_one);
	scanf("%i", &size_two);
	scanf("%i", &size_three);
	average = (size_one + size_two + size_three)/3;
	printf("The average of the trade sizes is %i.\n", average);
}