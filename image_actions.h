/*
* image_actions.h (header for .c)
*
* Faculty of Automatics and Computer Science, UPB
* Gheorghiu Doru-Vlad 312CA (21gheorghi@gmail.com)
* Homework #3 - Image editor (Year 1, Semester 1)
* © Copyright 2021
*/

#pragma once

#include "load_image.h"

//allocates matrix array depending on image type (1 mat=grayscale 3 mat=rgb)
double ***alloc_pixels(int width, int height, types type);

//returns the lenght of the matrix array
int lenght(types type);

//rounds a real number to a natural number
uint_fast8_t rounded(double x);

//clamps an integer between the values [0, 255]
double fclamp(double x);

//swaps two integers
void swap_int(int *x, int *y);

//reads all image info from an ascii file
double ***read_pixels(FILE *in_file, int width, int height, types type);

//reads all image info from a binary file
double ***read_pixels_binary(FILE *in_file, int width, int height, types
								   type);

//frees the memory of a matrix array depending on image type
void free_pixels(double ***matrix, int height, types type);
