#ifndef BUFFER_H
#define BUFFER_H

/*
 * Function prototypes
 */
 void initBuffer();
 char* getBufferStart();
 int getNumberCharsAvail();
 int getNumberCharsUsed();
 void closeBuffer();
 char* getNewBuffer(int numCharacters);
 char* getNewBufferAndCopy(int numCharacters);
 int getErrorNum();



#endif