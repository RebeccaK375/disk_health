#include <stdio.h>

main () {
	int size_one = 600, size_two = 100, size_three = 200;
	printf("The average number of shares traded is ");
	printf ("%i", (size_one + size_two + size_three)/3);
	printf ("\n");

	printf("Data Type   Bytes\n");
	printf("char        %i\n", sizeof(char));
	printf("short       %i\n", sizeof(short));
	printf("int         %i\n", sizeof(int));
	printf("long        %i\n", sizeof(long));
	printf("float       %i\n", sizeof(float));
}