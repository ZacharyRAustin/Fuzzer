#include <stdio.h>
#include <stdlib.h>
#include "FileManager.h"
#include "fuzzer.h"
#include "buffer.h"

int main(int argc, char** argv){
	if(argc < 2)
	{
		printf("Usage: ./fuzzer num_iterations [OPTIONAL] seed\n");
		fflush(stdout);
	}
	else
	{
		int num_iterations = atoi(argv[1]);
		if(num_iterations < 1)
		{
			openTemplate();
			copyTemplate();
			closeTemplate();
		}
		else
		{
			initBuffer();
			openTemplate();
			readTemplate();
			char* buffer = getBufferStart();
			
			if(argc > 2)
			{
				setRandSeed((unsigned int) atoi(argv[2]));
			}
			else
			{
				seedRand();
			}
			
			int i;
			int bufSize = getNumberCharsUsed();
			for(i = 0; i < num_iterations; i++)
			{
				fuzz(buffer, bufSize);
			}
			
			writeOutput();
			closeBuffer();
			closeTemplate();
		}

	}

	return 0;
}