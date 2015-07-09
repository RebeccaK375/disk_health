#include "program_controller.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//enum ATTRIBUTES{POWER_ON_HOURS, BLOCKS_READ, BLOCKS_WRITTEN, GLIST_COUNT, SCRUB_COUNT, GROWN_DEFECTS, IO_COUNT, IO_LATENCY, SENSE_ERRORS} attribute_enum;
int subattributes[]                 = {               1,             1,                 1,            1,             1,          3,           16,              5};
char* subattribute_names_in_order[] = {"POWER_ON_HOURS", "BLOCKS_READ", "BLOCKS_WRITTEN", "GLIST_COUNT", "SCRUB_COUNT", "IO_COUNT", "IO_LATENCY", "SENSE_ERRORS"};
int computation_type[]              = {           COUNT,         COUNT,            COUNT,         COUNT,         COUNT,      COUNT,        COUNT,           RATE};
double health_weight[]              = {         0.00001,             0,                0,    1000000000,             0,          0,            1,     5000000000};




int io_latency_weight_in_ms[] = {4, 8, 16, 30, 50, 100, 200, 400, 800, 2000, 4000, 16000, 30000, 45000, 60000, 1000000};



//***********************************************************************************************************************************************************//
//***********************************************************************************************************************************************************//
//********************* DO NOT TOUCH UNLESS YOU ADDED A NEW COMPLEX ATTRIBUTE WHICH REQUIRES A SPECIAL MANIPULATION OF ITS SUBATTRIBUTES*********************//
//***********************************************************************************************************************************************************//
//***********************************************************************************************************************************************************//

int compute_current_complex_value(int *args, int computation){
	switch (computation){
		case IO_LATENCY:	compute_io_latency(args, computation); 
							break; 
		default: 			compute_sum(args, computation);
	}
}

int compute_io_latency(int* args, int computation){
	int number_of_subattributes_to_weight = subattributes[computation];
	int counter, weighted_sum, number_ios;
	for(counter=0, weighted_sum=0, number_ios=0; counter<number_of_subattributes_to_weight; counter++){
		number_ios = number_ios + args[counter];
		weighted_sum = args[counter]*io_latency_weight_in_ms[counter];
	}
	int weighted_average = weighted_sum/number_ios;
	return weighted_average;
}


int compute_sum(int* args, int computation){
	int number_of_subattributes_to_sum = subattributes[computation];
	int counter;
	int sum;
	for (counter = 0, sum = 0; counter<number_of_subattributes_to_sum; counter++){
		sum = sum + args[counter];
	}
	return sum;
}

//char* complex_attribute_names_in_order = {"IO_COUNT", "IO_LATENCY", "SENSE_ERRORS"}

//char* complex_attribute_names = {}
//char* generic_attribute_names = {}
//char attribute_names = {"POWER_ON_HOURS", "BLOCKS_READ", "BLOCKS_WRITTEN", "GLIST_COUNT", "SCRUB_COUNT", "GROWN_DEFECTS", "IO_COUNT", "IO_LATENCY", "SENSE_ERRORS"}
/* Another possible layer of modularity is that the above array can change based on input */


/************************************** DO NOT EDIT ***********************************/

int num_attributes = sizeof(subattributes)/sizeof(*subattributes);