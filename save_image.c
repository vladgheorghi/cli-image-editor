/*
* save_image.c (source file for saving an image)
* (the image can be saved either in an ascii file or a binary file)
*
* Faculty of Automatics and Computer Science, UPB
* Gheorghiu Doru-Vlad 312CA (21gheorghi@gmail.com)
* Homework #3 - Image editor (Year 1, Semester 1)
* © Copyright 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "image_actions.h"
#include "load_image.h"
#include "save_image.h"

void save_image(char *filename, imagecreator image)
{
	//opens the file in write type
	FILE *out_file = fopen(filename, "w");

	types newtype = image.type;

	//converts the image type to binary if it was ascii
	if (newtype == P4)
		newtype = P1;
	else if (newtype == P5)
		newtype = P2;
	else if (newtype == P6)
		newtype = P3;

	char *type = type_to_string(newtype);

	//outputs image type
	fprintf(out_file, "%s\n", type);

	//outputs image width and height
	fprintf(out_file, "%d %d\n", image.width, image.height);

	//outputs image max value if it has
	if (image.type != P1 && image.type != P4)
		fprintf(out_file, "%hhu\n", image.max_value);

	int len = lenght(image.type); //lenght of matrix array

	uint_fast8_t pixel;

	//outputs image pixels
	for (int i = 0; i < image.height; i++) {
		for (int j = 0; j < image.width; j++)
			for (int k = 0; k < len; k++) {
				pixel = rounded(image.pixels[k][i][j]);
				fprintf(out_file, "%hhu ", pixel);
			}
		fprintf(out_file, "\n");
	}

	fprintf(stdout, "Saved %s\n", filename);

	//closes the file
	fclose(out_file);
}

void save_image_binary(char *filename, imagecreator image)
{
	//opens the file in binary write type
	FILE *out_file = fopen(filename, "wb");

	types newtype = image.type;

	//converts the image type to binary if it was ascii
	if (newtype == P1)
		newtype = P4;
	else if (newtype == P2)
		newtype = P5;
	else if (newtype == P3)
		newtype = P6;

	char *type = type_to_string(newtype);

	//outputs image type
	fwrite(&type[0], sizeof(char), 1, out_file);
	fwrite(&type[1], sizeof(char), 1, out_file);

	fwrite("\n", sizeof(char), 1, out_file);

	char width[MAXINTDECIMAL], height[MAXINTDECIMAL];

	//converts image width and height from integers to strings
	sprintf(width, "%d", image.width);
	sprintf(height, "%d", image.height);

	//outputs image width and height
	for (unsigned long i = 0; i < strlen(width); i++)
		fwrite(&width[i], sizeof(char), 1, out_file);
	fwrite(" ", sizeof(char), 1, out_file);
	for (unsigned long i = 0; i < strlen(height); i++)
		fwrite(&height[i], sizeof(char), 1, out_file);

	fwrite("\n", sizeof(char), 1, out_file);

	//outputs image max value if it has
	if (image.type != P1 && image.type != P4) {
		char max_value[MAX8BITDECIMAL];

		//converts image max value from integer to string
		sprintf(max_value, "%hhu", image.max_value);

		for (unsigned long i = 0; i < strlen(max_value); i++)
			fwrite(&max_value[i], sizeof(char), 1, out_file);
		fwrite("\n", sizeof(char), 1, out_file);
	}

	int len = lenght(image.type); //lenght of matrix array

	uint_fast8_t pixel;

	//outputs image pixels in binary
	for (int i = 0; i < image.height; i++)
		for (int j = 0; j < image.width; j++)
			for (int k = 0; k < len; k++) {
				pixel = rounded(image.pixels[k][i][j]);
				fwrite(&pixel, sizeof(uint_fast8_t), 1, out_file);
			}

	fprintf(stdout, "Saved %s\n", filename);

	//closes the file
	fclose(out_file);
}

char *type_to_string(types type)
{
	//returns image type as a string
	if (type == P1)
		return "P1";
	if (type == P2)
		return "P2";
	if (type == P3)
		return "P3";
	if (type == P4)
		return "P4";
	if (type == P5)
		return "P5";
	return "P6";
}
