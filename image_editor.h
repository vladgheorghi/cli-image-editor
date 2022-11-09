/*
* image_editor.h (header for .c)
*
* Faculty of Automatics and Computer Science, UPB
* Gheorghiu Doru-Vlad 312CA (21gheorghi@gmail.com)
* Homework #3 - Image editor (Year 1, Semester 1)
* © Copyright 2021
*/

#pragma once

//macro for maximum parameters number
#define MAXPARAM 5

//enum for command input (used to implement switch case)
typedef enum commands {
	EMPTY,
	LOAD,
	SELECT,
	SELECTALL,
	ROTATE,
	CROP,
	APPLY,
	APPLYFAIL,
	SAVE,
	SAVE_BINARY,
	EXIT,
	INVALID
} command;

//returns valid enum commands for switch case with parameters
command command_input(char *input, char **parameters);
