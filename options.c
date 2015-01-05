#include <stdlib.h>
#include "options.h"
#include "definitions.h"

//definitions==================================================================

//Typedefs=====================================================================
typedef struct cmdLineOptions_t{
	char* outputFile;
	char* templateFile;
	unsigned int seed;
	int seedGiven;
} cmdLineOptionsT;

//global class vars============================================================
cmdLineOptionsT options;

//Function prototypes==========================================================
int parseArg(char* arg);
int errno;
//Functions====================================================================
/*
 * Parse the given command line
 * and set the appropriate options in options typedef
 */
int parseCommandLine(int argc, char** argv){
	options.outputFile = NULL;
	options.templateFile = NULL;
	options.seedGiven = 0;
	errno = 0;

	return 0;
}

/*
 * Parse the specific argument and set it's option in cmdLineOptionsT
 * If the argument cannot be parsed, set errno and return
 * Otherwise return 0
 */
 int parseArg(char* arg){
 	return NULL;
 }

/*
 * Indicates whether a seed was given on the command line
 * Returns 1 if yes, 0 if no
 */
int seedGiven(){
	return options.seedGiven;
}

/*
 * Returns the seed provided via the command line
 */
unsigned int getSeed(){
	return options.seed;
}

/*
 * Indicates whether an output file name was given on the command line
 * Returns 1 if yes, 0 if no
 */
int outputGiven(){
	if(options.outputFile != NULL)
	{
		return 1;
	}

	return 0;
}

/*
 * Returns the name of the file the fuzzed template should be written to 
 */
char* getOutputFileName(){
	return options.templateFile;
}

/*
 * Indicates whether a template file name was given on the command line
 * Returns 1 if yes, 0 if no
 */
int templateGiven(){
	if(options.templateFile != NULL)
	{
		return 1;
	}

	return 0;
}

/*
 * Returns the name of the file the template should be read from
 */
char* getTemplateFileName(){
	return options.templateFile;
}