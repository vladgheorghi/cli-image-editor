/*
* rotate_image.c (source file for image rotation)
* (rotates the whole image or a square portion of it by an angle of:
* {0, +-90, +-180, +-270, +-360})
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
#include "rotate_image.h"
#include "load_image.h"

rotation rotate_image(imagecreator *image, char *angle_char, int *x1, int *y1,
					  int *x2, int *y2)
{
	int angle  = verify_angle(angle_char); //verifies angle is valid

	if (angle == -1) {
		fprintf(stdout, "Unsupported rotation angle\n");
		return INVALID_ANGLE;
	}

	//rotates the whole image if it is all selected
	if (*x1 == 0 && *y1 == 0 && *x2 == (*image).width && *y2 ==
		(*image).height) {
		if (angle == 90 || angle == -270) {
			(*image).pixels = rotate_whole_image_90(&(*image), &(*x2), &(*y2));
		} else if (angle == -90 || angle == 270) {
			(*image).pixels = rotate_whole_image_m90(&(*image), &(*x2),
													 &(*y2));
		} else if (angle == 180 || angle == -180) {
			(*image).pixels = rotate_whole_image_90(&(*image), &(*x2), &(*y2));
			(*image).pixels = rotate_whole_image_90(&(*image), &(*x2), &(*y2));
		}

		fprintf(stdout, "Rotated %s\n", angle_char);

		return ROTATED;
	} else if (*x2 - *x1 != *y2 - *y1) {
		fprintf(stdout, "The selection must be square\n");
		return NOT_SQUARE;
	}

	int side = *x2 - *x1; //selection square side

	int len = lenght((*image).type); //length of matrix array

	double ***matrix; //auxiliary matrix for selection rotation

	matrix = alloc_pixels(side, side, (*image).type); //allocates memory

	//auxiliary matrix becomes image selection
	for (int i = *y1; i < *y2; i++)
		for (int j = *x1; j < *x2; j++)
			for (int k = 0; k < len; k++)
				matrix[k][i - *y1][j - *x1] = (*image).pixels[k][i][j];

	//rotates matrix by specified angle
	if (angle == 90 || angle == -270) {
		rotate90(&matrix, side, (*image).type);
	} else if (angle == -90 || angle == 270) {
		rotate90(&matrix, side, (*image).type);
		rotate90(&matrix, side, (*image).type);
		rotate90(&matrix, side, (*image).type);
	} else if (angle == 180 || angle == -180) {
		rotate90(&matrix, side, (*image).type);
		rotate90(&matrix, side, (*image).type);
	}

	//image selection becomes auxiliary rotated matrix
	for (int i = *y1; i < *y2; i++)
		for (int j = *x1; j < *x2; j++)
			for (int k = 0; k < len; k++)
				(*image).pixels[k][i][j] = matrix[k][i - *y1][j - *x1];

	//frees the memory of the auxiliary matrix array
	free_pixels(matrix, side, (*image).type);

	fprintf(stdout, "Rotated %s\n", angle_char);
	return ROTATED;
}

int verify_angle(char *angle)
{
	//returns the angle as an integer if it is valid or -1 if not
	if (strcmp(angle, "-90") == 0)
		return -90;
	if (strcmp(angle, "90") == 0)
		return 90;
	if (strcmp(angle, "-180") == 0)
		return 180;
	if (strcmp(angle, "180") == 0)
		return -180;
	if (strcmp(angle, "-270") == 0)
		return -270;
	if (strcmp(angle, "270") == 0)
		return 270;
	if (strcmp(angle, "-360") == 0)
		return -360;
	if (strcmp(angle, "360") == 0)
		return 360;
	if (strcmp(angle, "0") == 0)
		return 0;
	return -1;
}

double ***rotate_whole_image_90(imagecreator *image, int *x2, int *y2)
{
	double ***matrix; //auxiliary matrix for whole image rotation

	int len = lenght((*image).type); //lenght of matrix array

	matrix = alloc_pixels((*image).height, (*image).width, (*image).type);

	int newi = 0, newj = 0;

	//auxiliary matrix becomes 90 degrees rotated image
	for (int j = 0; j < (*image).width; j++) {
		for (int i = (*image).height - 1; i >= 0; i--) {
			for (int k = 0; k < len; k++)
				matrix[k][newi][newj] = (*image).pixels[k][i][j];
			newj++;
		}
		newi++;
		newj = 0;
	}

	//frees the memory of the initial image
	free_pixels((*image).pixels, (*image).height, (*image).type);

	//swaps width height and selection of image
	swap_int(&(*image).height, &(*image).width);
	swap_int(&(*x2), &(*y2));

	//returns the new rotated image
	return matrix;
}

double ***rotate_whole_image_m90(imagecreator *image, int *x2, int *y2)
{
	double ***matrix; //auxiliary matrix for whole image rotation

	int len = lenght((*image).type); //lenght of matrix array

	matrix = alloc_pixels((*image).height, (*image).width, (*image).type);

	int newi = 0, newj = 0;

	//auxiliary matrix becomes -90 degrees rotated image
	for (int j = (*image).width - 1; j >= 0; j--) {
		for (int i = 0; i < (*image).height; i++) {
			for (int k = 0; k < len; k++)
				matrix[k][newi][newj] = (*image).pixels[k][i][j];
			newj++;
		}
		newi++;
		newj = 0;
	}

	//frees the memory of the initial image
	free_pixels((*image).pixels, (*image).height, (*image).type);

	//swaps width height and selection of image
	swap_int(&(*image).height, &(*image).width);
	swap_int(&(*x2), &(*y2));

	//returns the new rotated image
	return matrix;
}

void rotate90(double ****matrix, int N, types type)
{
	double aux;

	int len = lenght(type); //lenght of matrix array

	//uses known algorithm to rotate a squared matrix by 90 degrees
	for (int i = 0; i < N / 2; i++)
		for (int j = i; j < N - i - 1; j++)
			for (int k = 0; k < len; k++) {
				aux = (*matrix)[k][i][j];
				(*matrix)[k][i][j] = (*matrix)[k][N - 1 - j][i];
				(*matrix)[k][N - 1 - j][i] = (*matrix)[k][N - 1 - i][N - 1 - j];
				(*matrix)[k][N - 1 - i][N - 1 - j] = (*matrix)[k][j][N - 1 - i];
				(*matrix)[k][j][N - 1 - i] = aux;
			}
}
