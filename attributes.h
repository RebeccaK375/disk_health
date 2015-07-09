#ifndef ATTRIBUTE_HEADER_GUARD
#define ATTRIBUTE_HEADER_GUARD

#include <stdbool.h>
/**************	This file contains definitions for disks  attributes. ***********************/

/*	Complex attributes are disk attributes that are made up of several values. We can compute what that attribute 
	is at this moment in time (current_value) and what it was last time we checked it (previous_value). The delta
	is what we use to think about time series of this attribute - how has it performed over time. These generic 
	attributes can sometimes be made up of more than one attribute. For example, there are several types of IOs
	- reads, writes, verifies, etc. This generic attribute of IO is actually a sum of sub_attributes, each of which
	also have a value. sub_attribute structure variable is an array of all of those sub-attributes.*/

/* Instruction for altering: if you are changing this item, make sure to change:
		The complex_attribute constructor
		Add reader and writer for your specific structure variables
		Enumerate sub_attributes to make accessing O(1) operation*/


struct complex_attribute{
	int current_value;
	int previous_value;
	struct generic_attribute *sub_attributes[20];
};

/* Generic attributes are the lowest level of disk attributes available. These cannot be made up of other attributes.  */
struct generic_attribute{
	int current_value;
	int previous_value;
};

union union_attribute{
	struct complex_attribute *complex;
	struct generic_attribute *generic;
};

//typedef	union union_attribute ATTRIBUTE __attribute__ ((__transparent_union__));

struct tagged_attribute{
	char* name;
	enum{GENERIC_ATTRIBUTE, COMPLEX_ATTRIBUTE} code;
	union union_attribute *attribute;
};

struct flag{
	int code;
	char *name;
	bool value;
};

//struct complex_attribute* construct_complex_attribute(char*, int, int, ...);
struct complex_attribute* construct_complex_attribute(int, int*, int);
struct generic_attribute* construct_generic_attribute(int);
void read_generic_attribute(struct generic_attribute*);
void read_complex_attribute(struct complex_attribute*);
int ca_sub_attribute_value(struct complex_attribute*, int);
struct tagged_attribute* construct_tagged_attribute(int, int, int*);

#endif /*ATTRIBUTE_HEADER_GUARD*/



















