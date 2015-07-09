#include "program_controller.h"
#include "attributes.h"
#include "disk.h"

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>


// This will extract directory information
char** create_directory_string_array(char* directory, int* string_count){
	DIR *dp;
	struct dirent *ep;
	//char input_buffer[10][11];
	dp = opendir(directory);
	char* current_directory;

	char **string_array = NULL;
	int i = 0, strcount = 0;


	if (dp !=NULL){
		// readdir reads the next entry from the directory and returns a pointer to a structure containing information about the file.
		// returns a NULL pointer if there are no more entries
		while (ep = readdir (dp)){
			current_directory = ep->d_name;
			string_array = realloc(string_array, (strcount+1) * sizeof(char**));
			printf("Strcount = %i\n", strcount);
			printf("%s\n", current_directory);
			if((strcmp(current_directory, ".") != 0) && (strcmp(current_directory, "..") != 0)){
				string_array[strcount] = malloc((strlen(current_directory)+1)*sizeof(char*));
				string_array[strcount++] = strdup(current_directory);
			}
		}
		*string_count = strcount;
		(void) closedir(dp);

	} else{
		perror("Couldn't open the directory");
	}

	return string_array;
}


void free_directory_string_array(char** string_array, int* string_count){
	int i;
	for(i = 0; i < *string_count; i++){
		printf("currently freeing string_array[%d] with value %s\n", i, string_array[i]);
		free(string_array[i]);
	}
	free(string_array);
}


//Need a function which will determine if the directory is of interest

// This guy will determine which log to read

FILE* read_weekly_disk_file(char* filename){
	FILE* weekly_log;
	weekly_log = fopen(filename, "r");
	int a;
	int b;
	int c;
	char input[100];
	if(! weekly_log){
		printf("The attempt to open the weekly log failed!\n");
	} else{
		printf("SUCCESS!\n");
		read_disk_from_file(weekly_log);

	}

	return weekly_log;
}

int read_disk_from_file(FILE* file_pointer){
	printf("Executing read disk\n");
	char name[100];
	char serial[100];
	char vendor[100];
	char model[100];
	int rpm;
	char raid_type[100];
	int input[NUM_TO_PARSE];
	int limit, current_read;
	//fscanf(file_pointer, "%s%s%s%s", name, serial, vendor, model);
	fscanf(file_pointer, "%s%s%s%s%i%s", &name, &serial, &vendor, &model, &rpm, &raid_type);
	/*printf("Name = %s\nSerial = %s\nVendor = %s\nModel = %s\nRPM = %i\nRaid Type = %s\n",
		           name,         serial,       vendor,      model,     rpm,             raid_type);*/

	for(limit=0; limit < NUM_TO_PARSE; limit++){
		if(1==fscanf(file_pointer, "%i", &current_read)){
			input[limit] = current_read;
		}
	}

	/*for(limit=0; limit<num_to_parse; limit++){
		printf("Value %i = %i\n", limit, input[limit]);
	}*/
	read_disk(construct_disk(name, serial, vendor, model, rpm, raid_type, input));
	return 0;
}