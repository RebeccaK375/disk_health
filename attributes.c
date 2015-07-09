/**************	This file contains constructors, readers, and writers for disks and attributes ***********************/
#include "program_controller.h"
#include "attributes.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/********************************************************************************************
 ******************************* Generic Attribute Helpers **********************************
 *******************************************************************************************/

/* 	Constructor for generic attributes such as PowerOn Hours, Scrub Count, etc.
	@param	 name (string), current_value (integer)
	@return  pointer to a generic_attribute object

	Note: This will be used to populate complex attributes and disk objects*/

struct generic_attribute* construct_generic_attribute(int current_value){
	struct generic_attribute *ga_ptr;
	ga_ptr = malloc (sizeof (struct generic_attribute)); //allocate space at runtime
	ga_ptr->current_value = current_value;
	ga_ptr->previous_value = 0;
	return ga_ptr;
}

struct generic_attribute* update_generic_attribute(struct generic_attribute* ga_ptr, int current_value){
	ga_ptr->previous_value = ga_ptr->current_value;
	ga_ptr->current_value = current_value;
	return ga_ptr;
}

/* 	Reader for generic attributes. This function should be used when you are personally
	curious about the cntents of a generic_attribute. It will print out every structure
	variable of the object. Do not use this anywhere that might be executed through a call
	to "main" in health_monitor.c 

	@param	pointer to generic attribute
	@return void*/

void read_generic_attribute(struct generic_attribute* ga_ptr){
	printf("The generic_attribute current_value = %i\nThe generic_attribute previous_value = %i\n",
		                                          ga_ptr->current_value,                     ga_ptr->previous_value);
}


/********************************************************************************************
 ******************************* Complex Attribute Helpers **********************************
 *******************************************************************************************/


/* 	Constructor for complex attributes such as IOs, Sense Errors, etc.
	@param	 name (string), current_value (integer)
	@return  pointer to a complex_attribute object

	Note: This will be used to populate disk objects*/

struct complex_attribute* construct_complex_attribute(int num_args, int *args, int computation){
	struct complex_attribute *ca_ptr;
	ca_ptr = malloc (sizeof(struct complex_attribute)); // allocate space on runtime
	ca_ptr->current_value = compute_current_complex_value(args, computation);
	ca_ptr->previous_value = 0;

	int counter;
	for(counter = 0; counter < num_args; counter++){
		ca_ptr->sub_attributes[counter] = construct_generic_attribute(args[counter]);
	}
	return ca_ptr;
}


struct complex_attribute* update_complex_attribute(struct complex_attribute* ca_ptr, int num_args, int *args, int computation){
	ca_ptr->previous_value = ca_ptr->current_value;
	ca_ptr->current_value = compute_current_complex_value(args, computation);

	int counter;
	for(counter = 0; counter < num_args; counter++){
		update_generic_attribute(ca_ptr->sub_attributes[counter], args[counter]);
	}
	return ca_ptr;
}

/* 	Reader for complex attribute sub-attributes. Example: Sense Errors can take on
	6 different flavours: Type 1, Type 2.. etc. Thus, sense error complex attribute
	will contain 6 sub-attributes in an array. There is allocated space in Sense
	Error sub_attributes[] structure variable for 20 different sub-attributes, but
	Sense Error will only ever populate 6. This function will, given index of a
	sub-attribute return the name of the sub-attribute if it exists. Othewise, if the
	slot of the sub_attribute array is empty, it will return N/A.

	@param	pointer to complex attribute (struct complex_attribute)
			index (integer) indicating which slot of sub_attributes we want to explore
	@return name of the sub_attribute or N/A if the sub-attribute does not exist*/



int ca_sub_attribute_value(struct complex_attribute* ca_ptr, int index){
	int sub_attribute_value;

	if (ca_ptr->sub_attributes[index]){
		sub_attribute_value = ca_ptr->sub_attributes[index]->current_value;
	}else{
		sub_attribute_value = 0;
	}
	return sub_attribute_value;
}


/* 	Reader for complex attributes. This function should be used when you are personally
	curious about the contents of a complex_attribute. It will print out every structure
	variable of the object. Do not use this anywhere that might be executed through a call
	to "main" in health_monitor.c 

	@param	pointer to complex attribute
	@return void*/
void read_complex_attribute(struct complex_attribute* ca_ptr){
	int i = 0;
	printf("The complex_attribute current_value = %i\nThe generic_attribute previous_value = %i\n",
		                                          ca_ptr->current_value,                     ca_ptr->previous_value);

	printf("The sub-attributes of this are:");
		for (i = 0; i<20; i++){
			printf("%i, ", ca_sub_attribute_value(ca_ptr, i));
		}
}


/********************************************************************************************
 ******************************* Tagged Attribute Helpers **********************************
 *******************************************************************************************/

struct tagged_attribute* construct_tagged_attribute(int counter, int num_args, int *args){
	struct tagged_attribute *ta_ptr;
	ta_ptr = malloc (sizeof(struct tagged_attribute));
	ta_ptr->attribute = malloc(sizeof(union union_attribute));
	ta_ptr->name = subattribute_names_in_order[counter];
	if (num_args == 1){
		ta_ptr->code = GENERIC_ATTRIBUTE;
		ta_ptr->attribute->generic = construct_generic_attribute(args[0]);
	}else{
		ta_ptr->code = COMPLEX_ATTRIBUTE;
		ta_ptr->attribute->complex = construct_complex_attribute(num_args, args, counter); //computation code here
	}
	return  ta_ptr;
}


struct tagged_attribute* update_tagged_attribute(struct tagged_attribute *ta_ptr, int counter, int num_args, int *args){
	if (num_args == 1){   //GENERIC_ATTRIBUTE
		 update_generic_attribute(ta_ptr->attribute->generic, args[0]);
	}else{                //COMPLEX_ATTRIBUTE
		 update_complex_attribute(ta_ptr->attribute->complex, num_args, args, counter); //computation code here
	}
	return ta_ptr;
}