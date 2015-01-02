#include <stdio.h>
#include <stdlib.h>
#include "FileManager.h"
#include "fuzzer.h"
#include "buffer.h"

int main(int argc, char** argv){
	if(argc < 2)
	{
		printf("Usage: ./fuzzer num_iterations\n");
		fflush(stdout);
	}
	else
	{
		int num_iterations = atoi(argv[1]);
		if(num_iterations < 1)
		{
			openTemplate();
			copyTemplate();
			// printf("Value is: %d\n", val);
			closeTemplate();
		}
		else
		{
			initBuffer();
			openTemplate();
			readTemplate();
			char* buffer = getBufferStart();
			seedRand();
			int i;
			for(i = 0; i < num_iterations; i++)
			{

				fuzz(buffer);
			}
			
			writeOutput();
			closeBuffer();
			closeTemplate();
		}

	}

	return 0;
}