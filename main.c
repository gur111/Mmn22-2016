#include "common.h"

/* Global variables. */
complex comp[6];

int main() {
	int funcIndex, status;
	params *arguments = malloc(sizeof(params));
	bool newLineNeeded = { TRUE };
	getStartupText();
	while (TRUE) {
		getMarker(&newLineNeeded);
		newLineNeeded.x = TRUE;
		if ((funcIndex = getFunc(getInput(SPACE_CHAR))) == INVALID_FUNCTION)
			continue;
		if ((status = getArgs(&(cmd[funcIndex].info), getInput(NEWLINE),
				arguments)) != OK) {
			continue;
		}
		if (cmd[funcIndex].ptr == &empty) { /* Doesn't create a new line after an empty command. */
			newLineNeeded.x = FALSE;
			continue;
		}
		(cmd[funcIndex].ptr)(arguments);
	}/* End while */
	return 0;
}

/* Gets the text that appears when the program first starts */
void getStartupText(void) {
	printf("%s", STARTUP_TEXT ASSISTANCE);
}

/* Gets the marker sign that tells the user he can enter a command. */
void getMarker(bool *newLine) {
	if (newLine->x) {
		printf("%c$ ", NEWLINE);
	} else {
		printf(MARKER);
	}
	newLine->x = TRUE;
}

/* Gets the command and the arguments.
 * @return char pointer of the string input until the delimiter.
 * 			NULL on input too big.
 * 			returns string until the NEWLINE if no the limiter found prior.
 * 			returns "halt" string when EOF is found.
 */
char* getInput(char delim) {
	char *cmdStr = malloc(CMD_MAX_LEN);
	char ch;
	unsigned int i;

	while ((ch = getchar()) != NEWLINE && isspace(ch))
		; /* Ignore all whitespaces before  */
	for (i = 0; ch != delim; i++) { /* Restrict also reading after NEWLINE just in case the input did not include any spaces (Invalid input obviously) */
		if (i >= CMD_MAX_LEN) {
			free(cmdStr);
			while ((ch = getchar()) != NEWLINE && ch != EOF)
				; /* Skips the rest of the line. */
			return NULL;
		} else if (ch == EOF) {
			free(cmdStr);
			return HALT_NAME;
		} else if (ch == NEWLINE) {
			ungetc(ch, stdin);
			break;
		}
		if (i > 0 && isspace(cmdStr[i - 1])) /* Skipping whitespaces. */
			i--;
		cmdStr[i] = ch;
		ch = getchar();
	}
	cmdStr[i++] = '\0';
	/* Returning a pointer to the string with the proper storage amount. */
	return realloc(cmdStr, i);
}

/* Gets the pointer to the function with the given name and frees the name's input string. */
int getFunc(char* name) {
	if (name == NULL) {
		printErr(COMMAND_TOO_BIG, '\0');
		return INVALID_FUNCTION;
	}
	unsigned int i;
	for (i = 0; (cmd[i].ptr) != NULL; i++) {
		if (strcmp(cmd[i].name, name) == 0) {
			free(name); /* Remove input string from memory. */
			return i;
		}
	}
	printErr(INVALID_FUNCTION, '\0');
	free(name);
	free(getInput(NEWLINE)); /* Cleaning the rest of the line.  */
	return INVALID_FUNCTION; /* If not found. */
}

/* Create an array with all the entered arguments and returns a pointer to it. */
int getArgs(struct paramInfo* info, char* rawParam, params* args) {
	char* arg[3]; /* Pointers to the rawArgs separated. */
	char tmpCompName;
	int inputCount = 0;
	int validCount = 0;
	int status = OK;

	arg[0] = strtok(rawParam, SEPARATOR);
	if (info->argc > 1) {
		int i;
		for (i = 1; i < info->argc; i++) {
			arg[i] = strtok(NULL, SEPARATOR);
			if (arg[i] == NULL) {
				printErr(ARG_COUNT_FAILURE, '\0');
				return ARG_COUNT_FAILURE;
			}
		}
	}
	switch (info->argc) {
	case 3:
		if (info->cType == DOUBLE_TYPE) {
			inputCount += sscanf(arg[2], READ_D_S, &(args->vals[2].d),
					&tmpCompName);

		} else {
			inputCount += sscanf(arg[2], READ_C_S, &tmpCompName, &tmpCompName);
			if (comp_i(tmpCompName) < 0 || comp_i(tmpCompName) >= COMPLEX_COUNT) /* Macro validates name */
				status = INVALID_NAME;
			args->vals[2].c = &comp[comp_i(tmpCompName)];
		} /* End else (char type) */
		if ((validCount + 1) != inputCount) { /* No value was read successfully */
			printErr(WRONG_TYPE, 3); /* Send error, param 3 from wrong type.*/
			return WRONG_TYPE;
		} else if (status == INVALID_NAME) {
			printErr(INVALID_NAME, 3);
			return INVALID_NAME;
		} else
			validCount = inputCount;
		/* no break */
	case 2:
		if (info->bType == DOUBLE_TYPE) {
			inputCount += sscanf(arg[1], READ_D_S, &(args->vals[1].d),
					&tmpCompName);
		} else {
			inputCount += sscanf(arg[1], READ_C_S, &tmpCompName, &tmpCompName);
			if (comp_i(tmpCompName) < 0 || comp_i(tmpCompName) >= COMPLEX_COUNT) /* Macro validates name */
				status = INVALID_NAME;
			args->vals[1].c = &comp[comp_i(tmpCompName)];
		} /* End else (char type) */
		if ((validCount + 1) != inputCount) { /* No value was read successfully */
			printErr(WRONG_TYPE, 2); /* Send error, param 2 from wrong type.*/
			return WRONG_TYPE;
		} else if (status == INVALID_NAME) {
			printErr(INVALID_NAME, 2);
			return INVALID_NAME;
		} else
			validCount = inputCount;
		/* no break */
	case 1:
		if (info->aType == DOUBLE_TYPE) {
			inputCount += sscanf(arg[0], READ_D_S, &(args->vals[0].d),
					&tmpCompName);
		} else {
			inputCount += sscanf(arg[0], READ_C_S, &tmpCompName, &tmpCompName);
			if (comp_i(tmpCompName) < 0 || comp_i(tmpCompName) >= COMPLEX_COUNT) /* Macro validates name */
				status = INVALID_NAME;
			args->vals[0].c = &comp[comp_i(tmpCompName)];
		} /* End else (char type) */
		if ((validCount + 1) != inputCount) { /* No value was read successfully */
			printErr(WRONG_TYPE, 1); /* Send error, param 1 from wrong type.*/
			return WRONG_TYPE;
		} else if (status == INVALID_NAME) {
			printErr(INVALID_NAME, 1);
			return INVALID_NAME;
		} else
			validCount = inputCount;
		/* no break */
	}
	if (inputCount != info->argc) { /* This will never be true but just in case. */
		printErr(ARG_COUNT_FAILURE, '\0');/* if there was a problem with the arg count */
		return ARG_COUNT_FAILURE;	/* it would have been detected at the */
	}								/* beginning. if not, it's a problem with the arg type.*/
	return OK;

}

/* Prints the error of the given error number.*/
void printErr(int errorNum, int paramIndex) {
	if (paramIndex != '\0')
		printf("ERROR: %s Argument number: %c. %s", ERROR(errorNum), (char) CHAR_ZERO + paramIndex, ASSISTANCE);
	else
		printf("ERROR: %s%s", ERROR(errorNum), ASSISTANCE);
}

/* Shows the help text to the user.*/
void showHelp(void) {
	printf("%s",HELP_TEXT);
}

/* Shows information to the user.*/
void showInfo(void){
	printf("%s",INFO_TEXT);
}

/* Does nothing. To handle with returns with no text.*/
void empty(void) {
	return;
}
