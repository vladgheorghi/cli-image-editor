/*
* save_image.h (header file for .c)
*
* Faculty of Automatics and Computer Science, UPB
* Gheorghiu Doru-Vlad 312CA (21gheorghi@gmail.com)
* Homework #3 - Image editor (Year 1, Semester 1)
* © Copyright 2021
*/

#pragma once

#include "load_image.h"

//macro for maximum digits for integer
#define MAXINTDECIMAL 10

//macro for maximum digits for an 8-bit integer
#define MAX8BITDECIMAL 4

//converts image type to string
char *type_to_string(types type);

//saves image to a named ascii file
void save_image(char *filename, imagecreator image);

//saves image to a named binary file
void save_image_binary(char *filename, imagecreator image);
