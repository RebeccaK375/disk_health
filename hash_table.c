#include "hash_table.h"

#include <stdlib.h>
#include <stdarg.h>
#include "hash_table.h"
#include "disk.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


hash_table* create_hash_table(int size){
	hash_table *dictionary;
	int counter;

	if (size < 1){
		return NULL;
	} else{
		dictionary = malloc(sizeof(hash_table));
		dictionary->table = malloc(size*sizeof(linked_list));
		dictionary->size = size;
	}

	for(counter = 0; counter < size; counter++){
		dictionary->table[counter] = NULL;
	}
	return dictionary;
}


unsigned int disk_hash_value(hash_table *dictionary, char *disk_name){
	unsigned int hash_value = 0;
	for ( ; *disk_name != '\0'; disk_name++){
		hash_value = *disk_name + (hash_value << 5) - hash_value; //31 is our prime of choice
	}
	return hash_value % dictionary->size;
}


linked_list* lookup_hashed_disk(hash_table *dictionary, char* disk_name){
	linked_list *entry;
	unsigned int hash_value = disk_hash_value(dictionary, disk_name);
	for(entry = dictionary->table[hash_value]; entry != NULL; entry = entry->next){
		printf(entry != NULL ? "here" : "here2");
		if(strcmp(disk_name, entry->disk_name)){
			return entry;
		}
	}
	return NULL;
}


int commit_to_dictionary(hash_table *dictionary, struct disk *disk_ptr){
	linked_list *new_entry;
	linked_list *current_list;
	unsigned int hash_value = disk_hash_value(dictionary, disk_ptr->serial);

	new_entry = malloc(sizeof(linked_list));

	current_list = lookup_hashed_disk(dictionary, disk_ptr->serial);
	if (current_list){
		return 0;
	} else{
		new_entry->disk_name;
		new_entry->disk_object;
		new_entry->next = dictionary->table[hash_value];
		dictionary->table[hash_value] = new_entry;
	}
	return 0;
}



