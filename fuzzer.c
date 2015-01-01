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

int fuzz(char* b){
	int i;
	int bufSize = strlen(b);
	int cnt = 0;
	for(i = 0; i < bufSize + 1; i++)
	{
		if(changeCharacter())
		{
			b[i] = getRandomCharacter();
			cnt++;
		}
	}

	return cnt;
}

void seedRand(){
	srand((unsigned int) SEED);
}

int changeCharacter(){
	double probability = (double) rand() / (double) RAND_MAX;
	if(probability <= CHANGE_THRESHOLD)
	{
		return 1;
	}

	return 0;
}

char getRandomCharacter(){
	return (char) (32 + (rand() % 94));
}