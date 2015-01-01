#include "definitions.h"
#include "fuzzer.h"
#include <stdlib.h>
#include <string.h>

//defintions====================================================
#define SEED 54613846
#define CHANGE_THRESHOLD .2

//class vars====================================================


//function prototypes===========================================
int changeCharacter(); 
char getRandomCharacter();
//functions=====================================================

/*
 * For each character, if generated number is less than 
 * threshold, it is replaced with a randomly generated
 * character
 *
 * Returns the number of characters changed
 */
int fuzz(char* b){
	int i;
	int bufSize = strlen(b);
	int cnt = 0;
	for(i = 0; i < bufSize; i++)
	{
		if(changeCharacter())
		{
			b[i] = getRandomCharacter();
			cnt++;
		}
	}

	return cnt;
}

/*
 * Seeds the random number generator
 */
void seedRand(){
	srand((unsigned int) SEED);
}

/*
 * Checks to see if a generated number is less than or equal to
 * the given threshold.
 *
 * If it is, return 1
 * Otherwise, return 0
 */
int changeCharacter(){
	double probability = (double) rand() / (double) RAND_MAX;
	if(probability <= CHANGE_THRESHOLD)
	{
		return 1;
	}

	return 0;
}

/*
 * Gets a random character from ASCII 26 (space) to ASCII 126 (~)
 * --I think that math is right. Maybe. Whatever.
 */
char getRandomCharacter(){
	return (char) (32 + (rand() % 94));
}