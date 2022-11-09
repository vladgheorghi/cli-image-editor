/*
* crop_image.h (header file for .c)
*
* Faculty of Automatics and Computer Science, UPB
* Gheorghiu Doru-Vlad 312CA (21gheorghi@gmail.com)
* Homework #3 - Image editor (Year 1, Semester 1)
* © Copyright 2021
*/

#pragma once

#include "load_image.h"

//function for cropping an image (called in image_editor.c)
double ***crop_image(imagecreator * image, int *x1, int *y1, int *x2, int *y2);
