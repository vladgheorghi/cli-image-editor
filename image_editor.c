/*
* image_editor.c (main file)
* (command interface for image manipulation)
*
* Faculty of Automatics and Computer Science, UPB
* Gheorghiu Doru-Vlad 312CA (21gheorghi@gmail.com)
* Homework #3 - Image editor (Year 1, Semester 1)
* © Copyright 2021
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#include "apply_image.h"
#include "rotate_image.h"
#include "crop_image.h"
#include "save_image.h"
#include "exit.h"
#include "select_image.h"
#include "image_actions.h"
#include "load_image.h"
#include "image_editor.h"

#define ACTMAXLEN 6 //macro for maximum command lenght

int main(void)
{
	command comm = EMPTY;
	char *input = malloc(BUFSIZ * sizeof(char)); //each whole input goes here
	if (!input) {
		fprintf(stderr, "Failed malloc\n");
		exit(-1);
	}
	char *p, **parameters = malloc(MAXPARAM * sizeof(char *)); //each parameter
	if (!parameters) {
		fprintf(stderr, "Failed malloc\n");
		exit(-1);
	}
	imagecreator image; //stores all image info here
	status load_status = NOT_LOADED;
	int x1, y1, x2, y2; //selection coordinates

	while (comm != EXIT) {
		fgets(input, BUFSIZ, stdin); //reads each input command
		p = strchr(input, '\n');
		if (p)
			*p = '\0'; //deletes the newline at the end of fgets
		comm = command_input(input, parameters);
		if ((int)comm == -EXIT)
			comm = EXIT;
		switch (comm) {
		case LOAD: //loads the image
			load_status = load_image(parameters[0], &image,
									 &x1, &y1, &x2, &y2, load_status);
			break;
		case SELECT: //selects a portion of the image by given coordinates
			if (verify_load(load_status))
				select_pixels(&x1, &y1, &x2, &y2, parameters[0],
							  parameters[1], parameters[2], parameters[3],
							  image.width, image.height);
			break;
		case SELECTALL: //selects all the image's surface
			if (verify_load(load_status))
				select_all(&x1, &y1, &x2, &y2, image.width, image.height);
			break;
		case ROTATE: //rotates a selection of the image
			if (verify_load(load_status))
				rotate_image(&image, parameters[0],
							 &x1, &y1, &x2, &y2);
			break;
		case CROP: //crops the image to the current selection
			if (verify_load(load_status))
				image.pixels = crop_image(&image, &x1, &y1, &x2, &y2);
			break;
		case APPLY: //applies effects on a coloured image
			if (verify_load(load_status))
				apply_image(&image, parameters[0], x1, y1, x2, y2);
			break;
		case APPLYFAIL: //goes here if APPLY command has a valid input
			if (verify_load(load_status))
				fprintf(stdout, "Invalid command\n");
			break;
		case SAVE: //saves the image to a named file
			if (verify_load(load_status))
				save_image(parameters[0], image);
			break;
		case SAVE_BINARY: //saves the image to a named file in binary
			if (verify_load(load_status))
				save_image_binary(parameters[0], image);
			break;
		case EXIT: //frees all memory and exits the program
			if (verify_load(load_status)) {
				exit_program(&input, &parameters, &image, load_status);
			} else {
				free(input);
				free(parameters);
			}
			break;
		case EMPTY: //just for initial declaration
			break;
		case INVALID: //here goes all invalid inputs
			fprintf(stdout, "Invalid command\n");
			break;
		}
	}
	return 0;
}

//function for proper selection of valid inputs and parameters
command command_input(char *input, char **parameters)
{
	char **comm = malloc(MAXPARAM * sizeof(char *)), *tok = strtok(input, " ");
	int i = 0;
	while (tok && i < MAXPARAM) { //stores each command and parameter
		comm[i] = tok;
		tok = strtok(NULL, " ");
		i++;
	} //invalid inputs return INVALID, valid inputs return specified command
	if (strcmp(comm[0], "LOAD") == 0) {
		parameters[0] = comm[1];
		free(comm);
		return LOAD;
	} else if (strcmp(comm[0], "SELECT") == 0) {
		for (int j = 0; j < i - 1; j++)
			parameters[j] = comm[j + 1];
		free(comm);
		if (i == 2) {
			if (strcmp(parameters[0], "ALL") == 0)
				return SELECTALL;
			else
				return INVALID;
		} else if (i == 5) {
			for (int j = 0; j < 4; j++)
				for (unsigned long k = 0; k < strlen(parameters[j]); k++) {
					if ((parameters[j][k] < '0' || parameters[j][k] > '9') &&
						parameters[j][k] != '-')
						return INVALID;
					else if (parameters[j][k] == '-' && (parameters[j][k + 1]
							 < '0' || parameters[j][k + 1] > '9'))
						return INVALID;
				}
			return SELECT;
		} else {
			return INVALID;
		}
	} else if (strcmp(comm[0], "ROTATE") == 0) {
		if (i == 2) {
			parameters[0] = comm[1];
			free(comm);
			return ROTATE;
		}
		free(comm);
		return INVALID;
	} else if (strcmp(comm[0], "CROP") == 0) {
		free(comm);
		return CROP;
	} else if (strcmp(comm[0], "APPLY") == 0) {
		if (i == 2) {
			parameters[0] = comm[1];
			free(comm);
			return APPLY;
		} else if (i == 1) {
			free(comm);
			return APPLYFAIL;
		}
		free(comm);
		return INVALID;
	} else if (strcmp(comm[0], "SAVE") == 0) {
		if (i == 2) {
			parameters[0] = comm[1];
			free(comm);
			return SAVE_BINARY;
		} else if (i == 3) {
			if (strcmp(comm[2], "ascii") == 0) {
				parameters[0] = comm[1];
				parameters[1] = comm[2];
				free(comm);
				return SAVE;
			}
			free(comm);
			return INVALID;
		}
		free(comm);
		return INVALID;
	} else if (strcmp(comm[0], "EXIT") == 0) {
		free(comm);
		return -EXIT;
	}
	free(comm);
	return INVALID;
}

//function for verifying the load status of an image
int verify_load(status load_status)
{
	if (load_status == NOT_LOADED || load_status == LOAD_ERROR) {
		fprintf(stdout, "No image loaded\n");
		return 0;
	}
	return 1;
}
