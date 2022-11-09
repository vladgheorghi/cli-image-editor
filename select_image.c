/*
* select_image.c (selection function)
* (x1, y1, x2, y2 = coordinates)
*
* Faculty of Automatics and Computer Science, UPB
* Gheorghiu Doru-Vlad 312CA (21gheorghi@gmail.com)
* Homework #3 - Image editor (Year 1, Semester 1)
* © Copyright 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "image_actions.h"
#include "select_image.h"

void select_pixels(int *x1, int *y1, int *x2, int *y2, char *sx1, char *sy1,
				   char *sx2, char *sy2, int width, int height)
{
	int ax1, ay1, ax2, ay2;

	//converts coordinates from strings to integers using sscanf
	if (sscanf(sx1, "%d", &ax1) == 0) {
		fprintf(stderr, "Failed sscanf\n");
		exit(-1);
	}
	if (sscanf(sy1, "%d", &ay1) == 0) {
		fprintf(stderr, "Failed sscanf\n");
		exit(-1);
	}
	if (sscanf(sx2, "%d", &ax2) == 0) {
		fprintf(stderr, "Failed sscanf\n");
		exit(-1);
	}
	if (sscanf(sy2, "%d", &ay2) == 0) {
		fprintf(stderr, "Failed sscanf\n");
		exit(-1);
	}

	//verifies if coordinates are valid
	if (ax1 < 0 || ay1 < 0 || ax2 < 0 || ay2 < 0) {
		fprintf(stdout, "Invalid set of coordinates\n");

	} else if (ax1 > width || ay1 > height || ax2 > width || ay2 > height) {
		fprintf(stdout, "Invalid set of coordinates\n");

	} else if (ax1 == ax2 || ay1 == ay2) {
		fprintf(stdout, "Invalid set of coordinates\n");

	} else {
		*x1 = ax1;
		*y1 = ay1;
		*x2 = ax2;
		*y2 = ay2;

		//swaps coordinates if inputed unordered
		if (*x1 > *x2)
			swap_int(&(*x1), &(*x2));

		if (*y1 > *y2)
			swap_int(&(*y1), &(*y2));

		fprintf(stdout, "Selected %d %d %d %d\n", *x1, *y1, *x2, *y2);
	}
}

void select_all(int *x1, int *y1, int *x2, int *y2, int width, int height)
{
	//coordinates become the size of the image
	*x1 = 0;
	*y1 = 0;
	*x2 = width;
	*y2 = height;

	fprintf(stdout, "Selected ALL\n");
}
