#ifndef __FILE_MANAGER__
#define __FILE_MANAGER__

/*
 * Typedefs
 */

/*
 * Function Prototypes
 */
int openTemplate();
int readTemplate();
int writeOutput();
int closeTemplate();
void freeBuffer();
int copyTemplate();
char* getBuffer();

/*
 * Global Variables
 */

 #endif