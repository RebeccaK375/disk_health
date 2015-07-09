#ifndef HASH_HEADER_GUARD
#define HASH_HEADER_GUARD

/**************	This file contains definitions for disks ***********************/
typedef struct linked_list_struct{
	struct linked_list_struct *next;
	char *disk_name;
	struct disk *disk_object;
} linked_list;


typedef struct hash_table_struct {
	int size;
	linked_list **table;
} hash_table;

hash_table* create_hash_table(int);
unsigned int disk_hash_value(hash_table*, char*);
linked_list* lookup_hashed_disk(hash_table*, char*);
int commit_to_dictionary(hash_table*, struct disk*);


#endif /*HASH_HEADER_GUARD*/