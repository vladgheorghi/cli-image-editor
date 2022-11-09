/*
* image_actions.c (source file for standard functions)
* (functions explained in header file)
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

#include "load_image.h"
#include "image_actions.h"

double ***read_pixels(FILE *in_file, int width, int height, types type)
{
	double ***matrix;

	int len = lenght(type); //lenght of matrix array

	matrix = alloc_pixels(width, height, type); //allocates memory

	uint_fast8_t pixel;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < len; k++) {
				//reads matrix array from ascii file
				fscanf(in_file, "%hhu", &pixel);
				matrix[k][i][j] = (double)pixel;
			}

	return matrix;
}

double ***read_pixels_binary(FILE *in_file, int width, int height,
							 types type)
{
	double ***matrix;

	int len = lenght(type); //lenght of matrix array

	matrix = alloc_pixels(width, height, type); //allocates memory

	uint_fast8_t pixel;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < len; k++) {
				//reads matrix array from binary file
				fread(&pixel, sizeof(uint_fast8_t), 1, in_file);
				matrix[k][i][j] = (double)pixel;
			}

	return matrix;
}

void free_pixels(double ***matrix, int height, types type)
{
	int len = lenght(type); //lenght of matrix array

	//frees matrix array memory
	for (int k = 0; k < len; k++)
		for (int i = 0; i < height; i++)
			free(matrix[k][i]);
	for (int k = 0; k < len; k++)
		free(matrix[k]);
	free(matrix);
}

void swap_int(int *x, int *y)
{
	//used auxiliary variable for swapping because subtraction swap failed :(
	int aux;

	aux = (*x);
	(*x) = (*y);
	(*y) = aux;
}

double fclamp(double x)
{
	//negative numbers become 0 and numbers bigger than 255 become 255
	if (x <= 0)
		return 0.0;

	if (x >= 255)
		return 255.0;

	return x;
}

uint_fast8_t rounded(double x)
{
	//if x + 0.5 changes whole part then rounds superior else rounds inferior
	double y = x + 0.5;

	uint_fast8_t integerx = x, integery = y;

	if (integerx == integery)
		return integerx;
	else
		return integery;
}

int lenght(types type)
{
	if (type == P3 || type == P6)
		//P3 and P6 images are RGB so matrix array has lenght 3 for each colour
		return 3;

	//P1, P2, P4 and P5 images are grayscale so matrix array has lenght 1
	return 1;
}

double ***alloc_pixels(int width, int height, types type)
{
	int len = lenght(type); //lenght of matrix array

	double ***matrix = malloc(len * sizeof(double **));

	if (!matrix) {
		fprintf(stderr, "Failed malloc\n");
		exit(-1);
	}

	for (int k = 0; k < len; k++) {
		matrix[k] = malloc(height * sizeof(double *));

		if (!matrix[k]) {
			fprintf(stderr, "Failed malloc\n");
			exit(-1);
		}

		for (int i = 0; i < height; i++) {
			matrix[k][i] = malloc(width * sizeof(double));

			if (!matrix[k][i]) {
				fprintf(stderr, "Failed malloc\n");
				exit(-1);
			}
		}
	}

	return matrix;
}
