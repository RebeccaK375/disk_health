#include "program_controller.h"
#include "attributes.h"
#include "disk.h"
#include "hash_table.h"
#include "system.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

char data_directory[] = ".\\System";
char file_name[] = ".\\System\\DATA 03-14-2014 11-41-58";

int main() {
	printf ("I compiled.\n");
	//printf ("%i", POWER_ON_HOURS);
	//printf ("%s", data_directory);

	//print_directory(data_directory);

	health_monitor *starbucks;

	starbucks = malloc(sizeof(health_monitor));
	starbucks->id = "92838382";
	starbucks->disks_in_system = create_hash_table(10);


	printf("The size of the dictionary is %i\n", starbucks->disks_in_system->size);
	printf("The pointer for the hash_table is: %p\n", starbucks->disks_in_system);
	
	explore_current_directory(starbucks, data_directory);
    //read_weekly_disk_file(file_name);

    free(starbucks);
	return 0;
}


	char *id;
	struct disk *ordered_system_disks;
	int current_max_health;
	int current_min_health;
	struct _hash_table_ *didkd;
	hash_table *disks_in_system;