#ifndef FUZZER_H
#define FUZZER_H

/*
 * Function prototypes
 */
int fuzz(char* b, int bufSize);
void seedRand();
void setRandSeed(unsigned int s);

#endif