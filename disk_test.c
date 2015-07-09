/************ This file contains the unit tests disk structure, its constructors, writers, and readers ****************/
#include "program_controller.h"
#include "attributes.h"
#include "disk.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/*void test_generic_attribute_constructor(){
	struct generic_attribute* ga_ptr;
	ga_ptr = construct_generic_attribute(20000);
	printf("%p\n", ga_ptr);
}

void test_generic_attribute_reader(){
	struct generic_attribute* ga_ptr;
	ga_ptr = (struct generic_attribute*) construct_generic_attribute(20000);
	read_generic_attribute(ga_ptr);
}

void test_complex_attribute_constructor(){
	struct generic_attribute* ga_ptr1 = construct_generic_attribute(20);
	struct generic_attribute* ga_ptr2 = construct_generic_attribute(30);
	struct generic_attribute* ga_ptr3 = construct_generic_attribute(40);
	struct generic_attribute* array[] = {ga_ptr1, ga_ptr2, ga_ptr3};

	struct complex_attribute* ca_ptr = construct_complex_attribute(1000, 3, array);
	printf("%p\n", ca_ptr);
}

void test_complex_attribute_reader(){
	struct generic_attribute* ga_ptr1 = construct_generic_attribute(20);
	struct generic_attribute* ga_ptr2 = construct_generic_attribute(30);
	struct generic_attribute* ga_ptr3 = construct_generic_attribute(40);

	struct generic_attribute* array[] = {ga_ptr1, ga_ptr2, ga_ptr3};

	struct complex_attribute* ca_ptr = construct_complex_attribute(1000, 3, array);
	read_complex_attribute(ca_ptr);
}*/

void test_disk_constructor(){

	int input[] = {	1,    	//PQWER_ON_HOURS
					2, 		//BLOCKS READ
					100, 	//BLOCKS_WRITTEN
					20, 	//GLIST COUNT
					30, 	//SCRUB COUNT
					10, 	//GROWN DEFECTS
					100, 	//READS
					22, 	//WRITES
					300, 	//VERIFIES, TOTAL = 422
					10, 	//4ms
					300, 	//8ms
					100, 	//16ms
					20202, 	//30ms
					2, 		//50ms
					10, 	//100ms
					20, 	//200ms
					10, 	//400ms
					20, 	//800ms
					10, 	//2000ms
					20, 	//4000ms
					21, 	//16000ms
					22, 	//30000ms
					23, 	//45000ms
					24, 	//60000ms
					25, 	//1000000ms
					3,		//SENSE ERROR TYPE 1
					3,		//SENSE ERROR TYPE 2
					3,		//SENSE ERROR TYPE 3
					3,		//SENSE ERROR TYPE 4
					3};		//SENSE ERROR TYPE 5
					
	//struct *disk disk_ptr;
	//disk_ptr = malloc(sizeof())
	read_disk(construct_disk("test_disk", "dhdhdhd", "NETAPP", "SSD_MODEL", 720, "parity", input));
}

int main() {
	printf("Size of attribute array is: %i\n", num_attributes);
	//int input[] = {1, 2, 3};
	//struct tagged_attribute *ptr;
	//ptr = malloc(sizeof (struct tagged_attribute));
	//construct_tagged_attribute(1, input);
	//test_generic_attribute_constructor();
	//test_generic_attribute_reader();
	//test_complex_attribute_constructor();
	//test_complex_attribute_reader();
	test_disk_constructor();
	/*int k;
	int *kptr;
	kptr = &k;
	printf("kptr = %i\n", kptr);
	printf("*kpt = %i\n", *kptr);
	printf("&kptr = %i\n", &kptr);
	k = 5;
	printf("kptr = %i\n", kptr);
	printf("*kpt = %i\n", *kptr);
	printf("&kptr = %i\n", &kptr);
	*kptr = 10;
	printf("kptr = %i\n", kptr);
	printf("*kpt = %i\n", *kptr);
	printf("&kptr = %i\n", &kptr);
	printf("k = %i\n", k);

	int *p;
	//int al = 30;
	p = malloc(sizeof (int));
	*p = 30;
	printf("p = %i\n", p);
	printf("*p = %i\n", *p);
	printf("&(*p) = %i\n", &(*p));
	printf("&p = %i\n", &p);*/



}