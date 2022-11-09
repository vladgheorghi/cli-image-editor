/*
* rotate_image.h (header file for .c)
*
* Faculty of Automatics and Computer Science, UPB
* Gheorghiu Doru-Vlad 312CA (21gheorghi@gmail.com)
* Homework #3 - Image editor (Year 1, Semester 1)
* © Copyright 2021
*/

#pragma once

#include "load_image.h"

//enum for the rotation status of the image
typedef enum rotation_status {
	NO_ROTATION, //the image was not rotated yet
	ROTATED, //the image was rotated
	NOT_SQUARE, //the partial selection isn't squared therefore it can't rotate
	INVALID_ANGLE //the rotation angle is not {0, +-90, +-180, +-270, +-360}
} rotation;

//rotates a portion of the image by 90 degrees
void rotate90(double ****matrix, int N, types type);

//verifies if the angle is valid
int verify_angle(char *angle);

//rotates the whole image by 90 degrees even though it is not square-shaped
double ***rotate_whole_image_90(imagecreator *image, int *x2, int *y2);

//rotates the whole image by -90 degrees even though it is not square-shaped
double ***rotate_whole_image_m90(imagecreator *image, int *x2, int *y2);

//function for image rotation (called in image_editor.c)
rotation rotate_image(imagecreator *image, char *angle_char, int *x1, int *y1,
					  int *x2, int *y2);
