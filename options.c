#include <stdlib.h>
#include "options.h"
#include "definitions.h"

/*
 * Parse the given command line
 * and set the appropriate options in options typedef
 */
void parseCommandLine(int argc, char** argv){

}

/*
 * Indicates whether a seed was given on the command line
 * Returns 1 if yes, 0 if no
 */
int seedGiven(){
	return NULL;
}

/*
 * Returns the seed provided via the command line
 */
unsigned int getSeed(){
	return NULL;
}

/*
 * Indicates whether an output file name was given on the command line
 * Returns 1 if yes, 0 if no
 */
int outputGiven(){
	return NULL;
}

/*
 * Returns the name of the file the fuzzed template should be written to 
 */
char* getOutputFileName(){
	return NULL;
}

/*
 * Indicates whether a template file name was given on the command line
 * Returns 1 if yes, 0 if no
 */
int templateGiven(){
	return NULL;
}

/*
 * Returns the name of the file the template should be read from
 */
char* getTemplateFileName(){
	return NULL;
}