/*
* crop_image.c (source file for cropping an image)
* (crops the image to the current selection coordinates)
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

#include "crop_image.h"
#include "image_actions.h"
#include "load_image.h"

double ***crop_image(imagecreator *image, int *x1, int *y1, int *x2, int *y2)
{
	//new width and height matching the selection
	int newwidth = *x2 - *x1;
	int newheight = *y2 - *y1;

	//auxiliary matrix array for cropped image
	double ***matrix;

	int len = lenght((*image).type); //lenght of matrix array

	//allocates memory for the auxiliary matrix
	matrix = alloc_pixels(newwidth, newheight, (*image).type);

	//auxiliary matrix becomes image selection
	for (int i = *y1; i < *y2; i++)
		for (int j = *x1; j < *x2; j++)
			for (int k = 0; k < len; k++)
				matrix[k][i - *y1][j - *x1] = (*image).pixels[k][i][j];

	//frees the memory of the initial image
	free_pixels((*image).pixels, (*image).height, (*image).type);

	//updates image width and height with cropped image values
	(*image).width = newwidth;
	(*image).height = newheight;

	//coordinates match cropped image
	*x1 = 0;
	*y1 = 0;
	*x2 = newwidth;
	*y2 = newheight;

	fprintf(stdout, "Image cropped\n");

	//returns the cropped image that will replace the old image
	return matrix;
}
