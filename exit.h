/*
* exit.h (header file for .c)
*
* Faculty of Automatics and Computer Science, UPB
* Gheorghiu Doru-Vlad 312CA (21gheorghi@gmail.com)
* Homework #3 - Image editor (Year 1, Semester 1)
* © Copyright 2021
*/

#pragma once

#include "load_image.h"

//function to free the memory of used variables and marks the end of execution
void exit_program(char **input, char ***parameters, imagecreator * image,
				  status load_status);
