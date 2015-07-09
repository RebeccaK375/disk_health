#include "program_controller.h"
#include "hash_table.h"
#include "attributes.h"
#include "disk.h"
#include "system.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>

/* Go through directory, for each file name:
	- check if directory name is data
		- if yes, check if disk is new or old by checking the hash
			- if new, then construct disk and insert into dictionary
			- if old, then update the disk
		- if no, ignore
	- once you processed the disk, put in archive
	- normilize the disk_health and then rank the disks relative to each other
*/


/* Request N least healthy disks-> output*/

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


int process_current_directory(health_monitor* hm, char* directory){
    DIR *dp;
	struct dirent *ep;
	dp = opendir(directory);
    int counter;
    char* current_directory;

	if (dp !=NULL){
		// readdir reads the next entry from the directory and returns a pointer to a structure containing information about the file.
		// returns a NULL pointer if there are no more entries
		while (ep = readdir (dp)){
			if((strcmp(ep->d_name, ".") == 0) || (strcmp(ep->d_name, "..")==0)) {
				printf ("%s\n", "Scanning extraneous directories");
			}else{
				current_directory = ep->d_name;
				printf("Current directory is: %s\n\n\n", current_directory);
				if(lookup_hashed_disk(hm, current_directory)){
					printf("The first item in linked list is: %s\n", lookup_hashed_disk(hm, current_directory));
				}else{
					printf("I do not have this disk. Let me create one.\n");
					read_weekly_disk_file(concat(directory, concat("\\", current_directory)));
				}

				//if in hash, then update
				//if not in has, then construct and insert into hash
				//printf("%s\n", current_directory);

			}
		}
		(void) closedir(dp);
	} else{
		perror("Couldn't open the directory");
	}

	return 0;
}