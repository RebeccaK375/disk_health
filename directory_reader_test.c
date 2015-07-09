#include "directory_reader.h"

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>


char data_directory[] = ".\\System";
char file_name[] = ".\\System\\DATA 03-14-2014 11-41-58";

int main() {
	printf ("Commence Directory Reader Testing!\n");
	int* str_count_ptr;
	str_count_ptr = malloc(sizeof(int*));

	char** directory_array;
	directory_array = (char**) create_directory_string_array(data_directory, str_count_ptr);

	printf("The amount of strings in array = %i\n", *str_count_ptr);

	int i;
	for(i = 0; i < *str_count_ptr; i++){
		printf("strarray[%d] == %s\n", i, directory_array[i]);
	}

	free_directory_string_array(directory_array, str_count_ptr);
	free(str_count_ptr);
	return 0;
}