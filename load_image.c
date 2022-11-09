/*
* load_image.c (source file for image load)
* (reads binary or ascii file data and stores image using imagecreator struct)
*
* Faculty of Automatics and Computer Science, UPB
* Gheorghiu Doru-Vlad 312CA (21gheorghi@gmail.com)
* Homework #3 - Image editor (Year 1, Semester 1)
* © Copyright 2021
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "select_image.h"
#include "load_image.h"
#include "image_actions.h"

status load_image(char *filename, imagecreator *image, int *x1, int *y1,
				  int *x2, int *y2, status load_status)
{
	char newline; //reads each newline here
	FILE *in_file = fopen(filename, "r"); //opens the file in text read mode
	if (!in_file && load_status == LOADED) {
		fprintf(stdout, "Failed to load %s\n", filename);
		free_pixels((*image).pixels, (*image).height, (*image).type);
		return LOAD_ERROR;
	} else if (!in_file && load_status == NOT_LOADED) {
		fprintf(stdout, "Failed to load %s\n", filename);
		return LOAD_ERROR;
	}
	//frees the memory of the matrix array if an image is already loaded
	if (load_status == LOADED)
		free_pixels((*image).pixels, (*image).height, (*image).type);
	//reads image type as a string here
	char *imgtype = malloc(TYPELEN * sizeof(char));
	if (!imgtype) {
		fprintf(stderr, "Failed malloc\n");
		exit(-1);
	}
	fscanf(in_file, "%s", imgtype);
	fscanf(in_file, "%c", &newline);
	//assigns image type as a 'types' data type
	(*image).type = assign_type(imgtype);
	free(imgtype);
	skip_comment(in_file);
	//reads width and height of image
	fscanf(in_file, "%d", &(*image).width);
	fscanf(in_file, "%d", &(*image).height);
	fscanf(in_file, "%c", &newline);
	skip_comment(in_file);
	//reads image max value if possible
	if ((*image).type != P1 && (*image).type != P4) {
		fscanf(in_file, "%hhu", &(*image).max_value);
		fscanf(in_file, "%c", &newline);

		skip_comment(in_file);
	}

	//stores the file read position
	int pos = ftell(in_file);

	if ((*image).type == P1 || (*image).type == P2 || (*image).type == P3) {
		//Reads image in ascii
		(*image).pixels = read_pixels(in_file, (*image).width, (*image).height,
									  (*image).type);

		fclose(in_file);

	} else {
		//Reads image in binary
		fclose(in_file);

		//opens the file in binary read
		FILE *in_file = fopen(filename, "rb");

		if (!in_file) {
			fprintf(stdout, "Failed to load %s\n", filename);
			return LOAD_ERROR;
		}

		//reads from checkpoint position
		fseek(in_file, pos, SEEK_SET);

		(*image).pixels = read_pixels_binary(in_file, (*image).width,
											 (*image).height, (*image).type);

		fclose(in_file);
	}

	//assign the image coordinates to select all the image
	*x1 = 0;
	*y1 = 0;
	*x2 = (*image).width;
	*y2 = (*image).height;

	fprintf(stdout, "Loaded %s\n", filename);
	return LOADED;
}

types assign_type(char *imgtype)
{
	//returns a 'types' data type specifying the image type
	if (strcmp(imgtype, "P1") == 0)
		return P1;
	else if (strcmp(imgtype, "P2") == 0)
		return P2;
	else if (strcmp(imgtype, "P3") == 0)
		return P3;
	else if (strcmp(imgtype, "P4") == 0)
		return P4;
	else if (strcmp(imgtype, "P5") == 0)
		return P5;
	else
		return P6;
}

void skip_comment(FILE *in_file)
{
	char verifier;
	fscanf(in_file, "%c", &verifier);

	//reads commments as garbage
	if (verifier == '#') {
		do {
			fscanf(in_file, "%c", &verifier);
		} while (verifier != '\n');

	} else {
		fseek(in_file, -1, SEEK_CUR);
	}
}
