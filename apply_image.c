/*
* apply_image.c (source file for applying one of the four effects available)
*(effects can only be applied on RGB images)
*(effects are: EDGE, SHARPEN, BLUR and GAUSSIAN_BLUR)
*(uses image kernels to apply the effects)
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

#include "apply_image.h"
#include "image_actions.h"
#include "load_image.h"

status_apply apply_image(imagecreator *image, char *apply_str, int x1, int y1,
						 int x2, int y2)
{
	//assign the effect type
	applytype apply_type = assign_apply(apply_str);

	//returns APPLY_FAILED if the effect is invalid
	if (apply_type == INVALID_TYPE) {
		fprintf(stdout, "APPLY parameter invalid\n");
		return APPLY_FAILED;
	}

	//verifies if the image is Grayscale
	if ((*image).type != P3 && (*image).type != P6) {
		fprintf(stdout, "Easy, Charlie Chaplin\n");
		return NO_GRAYSCALE;
	}

	//applies the according effect to the image selection
	if (apply_type == -EDGE)
		apply_edge(&(*image), x1, y1, x2, y2);
	else if (apply_type == SHARPEN)
		apply_sharpen(&(*image), x1, y1, x2, y2);
	else if (apply_type == BLUR)
		apply_blur(&(*image), x1, y1, x2, y2);
	else if (apply_type == GAUSSIAN_BLUR)
		apply_gaussian_blur(&(*image), x1, y1, x2, y2);

	fprintf(stdout, "APPLY %s done\n", apply_str);

	return APPLY_DONE;
}

applytype assign_apply(char *apply_str)
{
	if (strcmp(apply_str, "EDGE") == 0)
		return -EDGE;
	if (strcmp(apply_str, "SHARPEN") == 0)
		return SHARPEN;
	if (strcmp(apply_str, "BLUR") == 0)
		return BLUR;
	if (strcmp(apply_str, "GAUSSIAN_BLUR") == 0)
		return GAUSSIAN_BLUR;
	return INVALID_TYPE;
}

void apply_edge(imagecreator *image, int x1, int y1, int x2, int y2)
{
	//EDGE image kernel
	static const double edge[3][3] = {
		{-1, -1, -1},
		{-1, 8, -1},
		{-1, -1, -1}
	};

	int len = lenght((*image).type); //lenght of matrix array

	double ***matrix; //auxiliary matrix for applying effect

	//allocates memory for auxiliary matrix
	matrix = alloc_pixels((x2 - x1), (y2 - y1), (*image).type);

	double sum;
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++) {
			if (i != 0 && j != 0 && i != (*image).height - 1 && j !=
				(*image).width - 1)
				for (int k = 0; k < len; k++) {
					//sums all products between kernel values and image values
					sum = (double)edge[0][0] * (*image).pixels[k][i - 1][j - 1]
					+ edge[0][1] * (*image).pixels[k][i - 1][j] +
					edge[0][2] * (*image).pixels[k][i - 1][j + 1] +
					edge[1][0] * (*image).pixels[k][i][j - 1] +
					edge[1][1] * (*image).pixels[k][i][j] +
					edge[1][2] * (*image).pixels[k][i][j + 1] +
					edge[2][0] * (*image).pixels[k][i + 1][j - 1] +
					edge[2][1] * (*image).pixels[k][i + 1][j] +
					edge[2][2] * (*image).pixels[k][i + 1][j + 1];

					//clamping the sum between 0 and 255
					matrix[k][i - y1][j - x1] = fclamp(sum);
				}
		}

	//the image selection becomes edged
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			if (i != 0 && j != 0 && i != (*image).height - 1 && j !=
				(*image).width - 1)
				for (int k = 0; k < len; k++)
					(*image).pixels[k][i][j] = matrix[k][i - y1][j - x1];

	//frees the memory of the auxiliary matrix
	free_pixels(matrix, y2 - y1, (*image).type);
}

void apply_sharpen(imagecreator *image, int x1, int y1, int x2, int y2)
{
	//SHARPEN image kernel
	static const double sharpen[3][3] = {
		{0, -1, 0},
		{-1, 5, -1},
		{0, -1, 0}
	};

	int len = lenght((*image).type); //lenght of matrix array

	double ***matrix; //auxiliary matrix for effect apply

	//allocates memory for the auxiliary matrix
	matrix = alloc_pixels((x2 - x1), (y2 - y1), (*image).type);

	double sum;
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++) {
			if (i != 0 && j != 0 && i != (*image).height - 1 && j !=
				(*image).width - 1)
				for (int k = 0; k < len; k++) {
					//sum of products between kernel values and image values
					sum = (double)sharpen[0][0] *
					(*image).pixels[k][i - 1][j - 1] +
					sharpen[0][1] * (*image).pixels[k][i - 1][j] +
					sharpen[0][2] * (*image).pixels[k][i - 1][j + 1] +
					sharpen[1][0] * (*image).pixels[k][i][j - 1] +
					sharpen[1][1] * (*image).pixels[k][i][j] +
					sharpen[1][2] * (*image).pixels[k][i][j + 1] +
					sharpen[2][0] * (*image).pixels[k][i + 1][j - 1] +
					sharpen[2][1] * (*image).pixels[k][i + 1][j] +
					sharpen[2][2] * (*image).pixels[k][i + 1][j + 1];

					//clamping the sum between 0 and 255
					matrix[k][i - y1][j - x1] = fclamp(sum);
				}
		}

	//image selection becomes sharpened
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			if (i != 0 && j != 0 && i != (*image).height - 1 && j !=
				(*image).width - 1)
				for (int k = 0; k < len; k++)
					(*image).pixels[k][i][j] = matrix[k][i - y1][j - x1];

	//frees the memory of the auxiliary matrix
	free_pixels(matrix, y2 - y1, (*image).type);
}

void apply_blur(imagecreator *image, int x1, int y1, int x2, int y2)
{
	//BLUR image kernel
	static const double blur[3][3] = {
		{1.0 / 9, 1.0 / 9, 1.0 / 9},
		{1.0 / 9, 1.0 / 9, 1.0 / 9},
		{1.0 / 9, 1.0 / 9, 1.0 / 9}
	};

	int len = lenght((*image).type); //lenght of matrix array

	double ***matrix; //auxiliary matrix for effect apply

	//allocates memory for the auxiliary matrix
	matrix = alloc_pixels((x2 - x1), (y2 - y1), (*image).type);

	double sum;
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++) {
			if (i != 0 && j != 0 && i != (*image).height - 1 && j !=
				(*image).width - 1)
				for (int k = 0; k < len; k++) {
					//sum of products
					sum = (double)blur[0][0] *
					(*image).pixels[k][i - 1][j - 1] +
					blur[0][1] * (*image).pixels[k][i - 1][j] +
					blur[0][2] * (*image).pixels[k][i - 1][j + 1] +
					blur[1][0] * (*image).pixels[k][i][j - 1] +
					blur[1][1] * (*image).pixels[k][i][j] +
					blur[1][2] * (*image).pixels[k][i][j + 1] +
					blur[2][0] * (*image).pixels[k][i + 1][j - 1] +
					blur[2][1] * (*image).pixels[k][i + 1][j] +
					blur[2][2] * (*image).pixels[k][i + 1][j + 1];

					//clamping the sum between 0 and 255
					matrix[k][i - y1][j - x1] = fclamp(sum);
				}
		}

	//image selection becomes BLURRY
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			if (i != 0 && j != 0 && i != (*image).height - 1 && j !=
				(*image).width - 1)
				for (int k = 0; k < len; k++)
					(*image).pixels[k][i][j] = matrix[k][i - y1][j - x1];

	//frees the memory of the auxiliary matrix
	free_pixels(matrix, y2 - y1, (*image).type);
}

void apply_gaussian_blur(imagecreator *image, int x1, int y1, int x2, int y2)
{
	//GAUSSIAN_BLUR kernel image
	static const double gblur[3][3] = {
		{1.0 / 16, 2.0 / 16, 1.0 / 16},
		{2.0 / 16, 4.0 / 16, 2.0 / 16},
		{1.0 / 16, 2.0 / 16, 1.0 / 16}
	};

	int len = lenght((*image).type); //lenght of matrix array

	double ***matrix; //auxiliary matrix for effect apply

	//allocates memory for the auxiliary matrix
	matrix = alloc_pixels((x2 - x1), (y2 - y1), (*image).type);

	double sum;
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++) {
			if (i != 0 && j != 0 && i != (*image).height - 1 && j !=
				(*image).width - 1)
				for (int k = 0; k < len; k++) {
					//sum of products
					sum = (double)gblur[0][0] *
					(*image).pixels[k][i - 1][j - 1] +
					gblur[0][1] * (*image).pixels[k][i - 1][j] +
					gblur[0][2] * (*image).pixels[k][i - 1][j + 1] +
					gblur[1][0] * (*image).pixels[k][i][j - 1] +
					gblur[1][1] * (*image).pixels[k][i][j] +
					gblur[1][2] * (*image).pixels[k][i][j + 1] +
					gblur[2][0] * (*image).pixels[k][i + 1][j - 1] +
					gblur[2][1] * (*image).pixels[k][i + 1][j] +
					gblur[2][2] * (*image).pixels[k][i + 1][j + 1];

					//clamping the sum between 0 and 255
					matrix[k][i - y1][j - x1] = fclamp(sum);
				}
		}

	//image selection becomes GAUSSIAN BLURRED
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			if (i != 0 && j != 0 && i != (*image).height - 1 && j !=
				(*image).width - 1)
				for (int k = 0; k < len; k++)
					(*image).pixels[k][i][j] = matrix[k][i - y1][j - x1];

	//frees the memory of the auxiliary matrix
	free_pixels(matrix, y2 - y1, (*image).type);
}
