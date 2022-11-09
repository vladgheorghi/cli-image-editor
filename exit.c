/*
* exit.c (source file for program exit)
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
#include "exit.h"

void exit_program(char **input, char ***parameters, imagecreator *image,
				  status load_status)
{
	free((*input));
	free((*parameters));
	if (load_status == LOADED)
		free_pixels((*image).pixels, (*image).height, (*image).type);
}
