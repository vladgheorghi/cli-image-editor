/*
* load_image.h (header file for .c)
*
* Faculty of Automatics and Computer Science, UPB
* Gheorghiu Doru-Vlad 312CA (21gheorghi@gmail.com)
* Homework #3 - Image editor (Year 1, Semester 1)
* © Copyright 2021
*/

#pragma once

//lenght for image type
#define TYPELEN 3

//enum for each image type (for easier code writing)
typedef enum types {P1, P2, P3, P4, P5, P6} types;

//the image struct
typedef struct image {
	types type;
	int width;
	int height;
	uint_fast8_t max_value;
	double ***pixels; //matrix array goes here
} imagecreator;

//enum for each load status
typedef enum load_stat {LOADED, LOAD_ERROR, NOT_LOADED} status;

//verifies the load status
// LOADED = the image was succesfully loaded
// LOAD_ERROR = there was an error in loading the image
// NOT_LOADED = no image was loaded
int verify_load(status load_status);

//function to skip file comments
void skip_comment(FILE *in_file);

//assigns enum types (convertor from 'string' to 'types' data type)
types assign_type(char *imgtype);

//the load function (called in image_editor.c) (returns a load status)
status load_image(char *filename, imagecreator *image,
				  int *x1, int *y1, int *x2, int *y2, status load_status);
