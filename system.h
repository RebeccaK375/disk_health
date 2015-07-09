#ifndef SYSTEM_HEADER_GUARD
#define SYSTEM_HEADER_GUARD

/**************	This file contains definitions for disks ***********************/


/* Disk structures represent individual disks within systems.*/
typedef struct system_struct {
	char *id;
	struct disk *ordered_system_disks;
	int current_max_health;
	int current_min_health;
	hash_table *disks_in_system;
} health_monitor;

int process_current_directory(hash_table*, char*);

#endif /*SYSTEM_HEADER_GUARD*/