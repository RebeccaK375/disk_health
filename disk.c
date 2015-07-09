/**************	This file contains constructors, readers, and writers for disks and attributes ***********************/
#include "program_controller.h"
#include "attributes.h"
#include "disk.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


/********************************************************************************************
 *************************************** Disk Helpers ***************************************
 *******************************************************************************************/

struct disk* construct_disk(char* name, char* serial, char* vendor, char* model, int RPM, char *raid_type, int *args){
	struct disk *disk_ptr;
	disk_ptr = malloc (sizeof (struct disk));
	disk_ptr->name = name;
	disk_ptr->serial = serial;
	disk_ptr->vendor = vendor;
	disk_ptr->model = model;
	disk_ptr->RPM = RPM;
	disk_ptr->raid_type = raid_type;

	int counter, incrementer, index;
	// Counter indicates which attribute is being populated for the disk
	// Incrementer indicates how many sub-attributes to "eat up" from the input  <---- reality
	// index indicates how many sub-attributes are expected to be consumed  <----- expectation
	// What happens when reality != expectation is TBD

	incrementer = subattributes[counter];

	for(counter = 0, index = 0; counter < num_attributes; counter++, index = index + incrementer, incrementer = subattributes[counter]){
		//printf("Counter = %i\n", counter);
		//printf("incrementer = %i\n", incrementer);
		//printf("index = %i\n", index);
		disk_ptr->attribute_ptr[counter] = malloc (sizeof (struct tagged_attribute));
		disk_ptr->attribute_ptr[counter] = construct_tagged_attribute(counter, incrementer, &args[index]); 
		// figure out how to give these attributes names/types if need be
	}
	disk_ptr->health = 0;
	disk_ptr->health = compute_disk_health(disk_ptr);
	disk_ptr->health_normalized = 0;
	return disk_ptr;
}



struct disk* update_disk(struct disk* disk_ptr, char* name, char* serial, char* vendor, char* model, int RPM, char *raid_type, int *args){
	disk_ptr->raid_type = raid_type;
	int counter, incrementer, index;

	incrementer = subattributes[counter];

	for(counter = 0, index = 0; counter < num_attributes; counter++, index = index + incrementer, incrementer = subattributes[counter]){
		update_tagged_attribute(disk_ptr->attribute_ptr[counter], counter, incrementer, &args[index]); 
	}

	disk_ptr->health = compute_disk_health(disk_ptr);
	return disk_ptr;
}





void read_disk(struct disk* disk_ptr){

	printf("Disk name = %s\nSerial = %s\nVendor = %s\nModel = %s\nRPM = %i\nRaid type = %s\n",  
			disk_ptr->name, disk_ptr->serial,disk_ptr->vendor,disk_ptr->model,disk_ptr->RPM,disk_ptr->raid_type);
	printf("The attributes in the disk are:\n");
	int counter;
	for(counter = 0; counter<num_attributes; counter++){
		printf("%s = %i\n", disk_ptr->attribute_ptr[counter]->name, ((disk_ptr->attribute_ptr[counter]->code == GENERIC_ATTRIBUTE)? 
			                                                                           disk_ptr->attribute_ptr[counter]->attribute->generic->current_value :
		                                                                               disk_ptr->attribute_ptr[counter]->attribute->complex->current_value));
	}

	printf("DISK HEALTH IS:%lf\n", disk_ptr->health);
}

double compute_health_contribution(struct disk* disk_ptr, int counter){
	double attribute_current = (double) extract_attribute_current(disk_ptr, counter);
	double attribute_previous = (double) extract_attribute_previous(disk_ptr, counter);
	double attribute_processed;
	switch (counter){
		case COUNT: 	attribute_processed = attribute_current;
		case RATE:		attribute_processed = ((double) (attribute_current - attribute_previous))/ ((double) blocks_processed_delta(disk_ptr));
		default: 		attribute_processed = attribute_current;
	}

	return (double) (attribute_processed*health_weight[counter]);
}


double compute_disk_health(struct disk* disk_ptr){
	int counter;
	double health;
	double current_health = 0;
	double previous_health = disk_ptr->health;
	for(counter=0; counter < num_attributes; counter++){
		current_health = current_health + compute_health_contribution(disk_ptr, counter);
	}
	health = ALPHA*current_health + (1-ALPHA)*previous_health;
	return health;

}


//****************Getters for tagged attributes *********************//

int extract_attribute_current (struct disk* disk_ptr, int counter){
	return ((disk_ptr->attribute_ptr[counter]->code == GENERIC_ATTRIBUTE)? 
			                                        disk_ptr->attribute_ptr[counter]->attribute->generic->current_value :
		                                            disk_ptr->attribute_ptr[counter]->attribute->complex->current_value);
}

int extract_attribute_previous (struct disk* disk_ptr, int counter){
	return ((disk_ptr->attribute_ptr[counter]->code == GENERIC_ATTRIBUTE)? 
			                                        disk_ptr->attribute_ptr[counter]->attribute->generic->previous_value :
		                                            disk_ptr->attribute_ptr[counter]->attribute->complex->previous_value);
}

int blocks_processed_delta (struct disk* disk_ptr){
	int current = extract_attribute_current(disk_ptr, BLOCKS_READ) + extract_attribute_current(disk_ptr, BLOCKS_WRITTEN);
	int previous = extract_attribute_previous(disk_ptr, BLOCKS_READ) + extract_attribute_previous(disk_ptr, BLOCKS_WRITTEN);
	return current-previous;
}

/* function calcHealtMovingStrategy(obj)
            alpha = evalin('base', 'Alpha;');
            alpha_sc = evalin('base', 'Alpha_Scrub;');
            alpha_mn = evalin('base', 'Alpha_Maintanance;');
            
            T1_W = evalin('base', 'T1_W;');
            T3_W = evalin('base', 'T3_W;');
            TO_W = evalin('base', 'TO_W;');
            RT_W = evalin('base', 'RT_W;');
            PO_W = evalin('base', 'PO_W;');
            RTH_W = evalin('base', 'RTH_W;');
            
            T1 = obj.Type1_Errors_Rate_Current;
            T3 = obj.Type3_Errors_Rate_Current;
            TO = obj.Timeout_Rate_Current;
            REQ = obj.Request_Time_Current;
            REQ_H = obj.Request_Time_High;
            SCR = obj.Scrub_Count_Delta;
            POH = obj.PowerOnHours;
            obj.Health_Prior = obj.Health_Current;
            
            if SCR >0
                alpha = alpha_sc;
            end
            
            if obj.Status == 1
                alpha = alpha_mn;
            end
        
            current_estimation = T1_W*T1 + T3_W*T3 + TO_W*TO + RT_W*REQ + PO_W*POH + RTH_W*REQ_H;
            obj.Health_Current = alpha*current_estimation + (1-alpha)*obj.Health_Prior;
        end
*/

	/*va_list ap;
	va_start(ap, num_args);
	struct generic_attribute* max;
	int counter;
	// 	No assumption about the number of sub-attributes that an object might have
	// 	Reason: IO latencies have 16 possible sub-attributes. Sense Errors have 6
	//	possible choices. I decided that having a generic object will let us handle
	//	different cases more efficiently. Talk to me if this is not ok.
	for(counter = 0; counter < num_args; counter++){        
		ca_ptr -> sub_attributes[counter] = va_arg(ap, struct generic_attribute*);
	}
	va_end(ap);
	return ca_ptr;*/
