/*
 * common.h
 *
 *  Created on: Dec 19, 2015
 *      Author: gur
 */

#define TRUE 1
#define FALSE 0
#define MAX_ARG_COUNT 3
#define CMD_MAX_LEN 100 /* Max length for the name and for the arguments string. */
#define MARKER "$ "
#define ASSISTANCE "Type 'help' for instructions."
#define SEPARATING_LINE "###########################################################################\n"
#define HELP_TEXT SEPARATING_LINE\
					"Enter one of the following function in a valid form.\n"\
					"Usage: {FUNCTION_NAME} {PARAM_1},{PARAM_2},{PARAM_3}\n"\
					"Enter 'info' for more about form structure and parameters' types.\n\n"\
					"Functions:\n"\
					"read_comp \t\t{VAR_NAME},{REAL},{IMAGINARY}\n\tReads values into a complex variable.\n"\
					"print_comp \t\t{VAR_NAME}\n\tPrints a complex variable.\n"\
					"add_comp \t\t{VAR_NAME},{VAR_NAME}\n\tPrints the result of adding two complex variables.\n"\
					"sub_comp \t\t{VAR_NAME},{VAR_NAME}\n\tPrints the result of subtracting two complex variables.\n"\
					"mult_comp_real \t\t{VAR_NAME},{VAR_NAME},{REAL}\n\tPrints the result of multiplication of complex with real number.\n"\
					"mult_comp_img \t\t{VAR_NAME},{VAR_NAME},{IMAGINARY}\n\tPrints the result of multiplication of complex with imaginary.\n"\
					"abs_comp \t\t{VAR_NAME}\n\tPrints the absolute value of a complex variable.\n"\
					"help\n\tThis page.\n"\
					"info\n\tInfo about usage and licensing of the program.\n"\
					SEPARATING_LINE
#define STARTUP_TEXT SEPARATING_LINE "Welcome to the Complex Calculator. ©2015 Gur Telem.\n" SEPARATING_LINE

#define INFO_TEXT STARTUP_TEXT\
					"The program handles input texts pretty well, it ignores whitespace (except for the one space after function_name). "\
					"Also ignores multiple commas (refers as a single comma). "\
					"The input is limited to max of 200 characters (not including whitespaces), 100 for the function name and 100 for the parameters text. "\
					"Command is built in the form of \n\t{spaceless_function_name} {optional_param_1},{optional_param_2},{optional_param_3}\n"\
					"Function name + space + parameters separated with commas. "\
					"Both the space and the parameters are optional and depend on the function. "\
					"The program include two types of input arguments, a single character and a real number. "\
					"Single characters are representation of variables' names. There are 6 variable names with capital letters (A-F).\n"\
					"IMPORTANT NOTICE! \n\tNewlines are not considered whitespaces but separators between commands.\n"\
					"\tImaginary numbers are represented as real numbers in the input.\n"\
					"\tExcept for read_comp, no function changes the actual values of the variables.\n"\
					"Input with more arguments than needed is allowed but the extra arguments will be ignored. "\
					"\n\n"\
					"The program was built as an assignment work for the Open University.\n"\
					"The program is registered under GPL License. See License.txt for more information.\n"\
					"The source code can be found here: https://github.com/gur111/Mmn22-2016.git\n"\
					"The complex calculator can handle simple complex operations and most of the programming is focused on the UI.\n"\
					"If you want to embed parts of the code in other programs feel free to do so but please give credit :)\n"\
					"Enjoy!\n"\
					SEPARATING_LINE
#define FIRST_NAME 'A' /* First Argument Name */
#define COMPLEX_COUNT 6 /* Number Of Arguments */
#define ERROR(a) error[a+1]
#define HALT_NAME "halt"
/* Contsants. */
#define NEWLINE '\n'
#define SPACE_CHAR ' '
#define SEPARATOR "," /* Separator between arguments */
#define CHAR_ZERO '0'
#define DOUBLE_TYPE 1
#define CHAR_TYPE 0
#define READ_C_S "%c%c"  /* Reading char string. Another one to make sure no other chars are connected*/
#define READ_D_S "%lf%c" /* Reading double string. */
#define comp_i(x) x - FIRST_NAME /* Getting the letter index starting from FIRST_NAME */
enum {
	INVALID_FUNCTION = -1,
	WRONG_TYPE,
	ARG_COUNT_FAILURE,
	COMMAND_TOO_BIG,
	INVALID_NAME,
	OK
};

const char *error[] = {
		"Invalid function. ",
		"Wrong argument type. ",
		"Not enough arguments. ",
		"The command string is too big. ",
		"Invalid argument name. "
};

/* Includes. */
/* <stdio.h> <stdlib.h> not needed because they appear in compleX.h */
#include <string.h>
#include <ctype.h>
#include "compleX.h"

/* Type defines. */
typedef void (*function)();
typedef struct {
	char* name;
	function ptr;
	struct paramInfo{
		unsigned int argc: 2;
		unsigned int aType: 1;
		unsigned int bType: 1;
		unsigned int cType: 1;
	}info;	/* argc is the amount of arguments needed.
	 	 	 * aType, bType and cType are the type of the 1st-3rd argument's type.
	 	 	 * WARNING! The program assumes that functions require top of MAX_ARG_COUNT arguments.
	 	 	 */
} functionCard;
typedef struct{
	unsigned int x: 1;
}bool;

/* Functions declarations. */
char* getInput(char);
void println(char *);
void getStartupText(void);
void getMarker(bool*);
int getFunc(char *);
int getArgs(struct paramInfo*, char *, params*);
void sortCmd(functionCard array);
void printErr(int, int);
void showHelp(void);
void showInfo(void);
void empty(void); /* Dummy function. */

/* Stores all the "function cards". Contains function name, pointer and parameters information */
functionCard cmd[] = {
		{"read_comp", 		&read_comp, 	{3, CHAR_TYPE, DOUBLE_TYPE,DOUBLE_TYPE}},
		{"print_comp",	 	&print_comp,	{1, CHAR_TYPE}},
		{"add_comp", 		&add_comp,		{2, CHAR_TYPE, CHAR_TYPE}},
		{"sub_comp",		&sub_comp,		{2, CHAR_TYPE, CHAR_TYPE}},
		{"mult_comp_real", 	&mult_comp_real,{2, CHAR_TYPE, DOUBLE_TYPE}},
		{"mult_comp_img",	&mult_comp_img,	{2, CHAR_TYPE, DOUBLE_TYPE}},
		{"mult_comp_comp",	&mult_comp_comp,{2, CHAR_TYPE, CHAR_TYPE}},
		{"abs_comp",		&abs_comp,		{1, CHAR_TYPE}},
		{HALT_NAME,			&halt,			{0}},
		{"help",			&showHelp,		{0}},
		{"info",			&showInfo,		{0}},
		{"",				&empty},
		{"Invalid_function",NULL}
};
