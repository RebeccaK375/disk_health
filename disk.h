#ifndef DISK_HEADER_GUARD
#define DISK_HEADER_GUARD

/**************	This file contains definitions for disks ***********************/


/* Disk structures represent individual disks within systems.*/
struct disk {
	char *name;
	char *serial;
	char *vendor;
	char *model;
	int RPM;
	char *raid_type;

	/*This might look strange and you might ask "Why do this weird array thing when you can just list
	  the different attributes and make each of them separate. The answer is that all of the attributes
	  have the same types of values and follow the same format. If you ever decide to introduce a new 
	  attribute, all you have to do is change the size of arrays below and the parser for files. The 
	  program will treat your new attributes just as generic or complex attributes and do everything
	  right without you having to re-write constructors, readers, etc.*/

	struct flag *flag_ptr[20];
	struct tagged_attribute *attribute_ptr[100];
	double health;
	int health_normalized;
};

struct disk* construct_disk(char*, char*, char*, char*, int, char*, int*);
struct disk* update_disk(struct disk*, char*, char*, char*, char*, int, char*, int*);
void read_disk(struct disk*);
double compute_disk_health(struct disk*);
double compute_health_contribution(struct disk*, int);
int extract_attribute_current(struct disk*, int);
int extract_attribute_previous(struct disk*, int);
int blocks_processed_delta (struct disk*);

#endif /*DISK_HEADER_GUARD*/