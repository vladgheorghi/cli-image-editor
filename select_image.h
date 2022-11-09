/*
* select_image.h (header file for .c)
*
* Faculty of Automatics and Computer Science, UPB
* Gheorghiu Doru-Vlad 312CA (21gheorghi@gmail.com)
* Homework #3 - Image editor (Year 1, Semester 1)
* © Copyright 2021
*/

#pragma once

//selects a portion of the image
void select_pixels(int *x1, int *y1, int *x2, int *y2, char *sx1, char *sy1,
				   char *sx2, char *sy2, int width, int height);

//selects whole image's surface
void select_all(int *x1, int *y1, int *x2, int *y2, int width, int height);
