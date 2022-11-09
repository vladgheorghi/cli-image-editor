/*
* apply_image.h (header file for .c)
*
* Faculty of Automatics and Computer Science, UPB
* Gheorghiu Doru-Vlad 312CA (21gheorghi@gmail.com)
* Homework #3 - Image editor (Year 1, Semester 1)
* © Copyright 2021
*/

#pragma once

#include "load_image.h"

//enum for effect type
typedef enum apply_type {
	EDGE,
	SHARPEN,
	BLUR,
	GAUSSIAN_BLUR,
	INVALID_TYPE
} applytype;

//enum for apply status
typedef enum status_apply {
	APPLY_DONE, //the effect has been succesfully applied to image selection
	APPLY_FAILED, //the effect has failed to be applied
	NO_GRAYSCALE //the image is grayscale, therefore no effects can be applied
} status_apply;

//applies edge effect to the RGB image
void apply_edge(imagecreator *image, int x1, int y1, int x2, int y2);

//applies the sharpen effect to the RGB image
void apply_sharpen(imagecreator *image, int x1, int y1, int x2, int y2);

//applies the blur effect to the RGB image
void apply_blur(imagecreator *image, int x1, int y1, int x2, int y2);

//applies the gaussian blur effect to the RGB image
void apply_gaussian_blur(imagecreator *image, int x1, int y1, int x2, int y2);

//assigns the apply type (converts string to 'applytype' data type)
applytype assign_apply(char *apply_str);

//function for applying an effect to a RGB image (called in image_editor.c)
status_apply apply_image(imagecreator *image, char *apply_str, int x1, int y1,
						 int x2, int y2);
