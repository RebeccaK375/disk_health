#ifndef PROGRAM_CONTROLLER_HEADER_GUARD
#define PROGRAM_CONTROLLER_HEADER_GUARD

#define NUM_TO_PARSE 29

/**************************** HEALTH METRIC CONSTANTS **************************/

#define ALPHA 0.7
#define ALPHA_SCRUB 0.8
#define ALPHA_MAINTANANCE 0.9
#define DIRECTORY ".\\System"

/* 	By making changes to this header, you can ultimately make all of the changes necessary
	to add or remove attributes. If you wihs to add or remova any standard attribute or flag,
	simply edit the enumerations below. Please note that this is a standard and editing this
	standard incorrectly WILL break this code. */

enum ATTRIBUTES 		{POWER_ON_HOURS, BLOCKS_READ, BLOCKS_WRITTEN, GLIST_COUNT, SCRUB_COUNT, IO_COUNT, IO_LATENCY, SENSE_ERRORS, ABRAKADABRA} attribute_enum;
enum COMPUTATION_TYPE 	{COUNT, RATE, THRESHOLD};

enum FLAGS {FIRST_MEDIA_ERROR, FIRST_IO_LATENCY_HIGH} flag_enum;

extern int subattributes[];
extern char* subattribute_names_in_order[];
extern int num_attributes;
extern int io_latency_weight_in_ms[];
extern double health_weight[];

//extern int num_to_parse;


int compute_current_complex_value(int*, int);
int compute_io_latency(int*, int);
int compute_sum(int*, int);

#endif /*PROGRAM_CONTROLLER_HEADER_GUARD*/