#include <stdio.h>
#include <stdlib.h>
#include "FileManager.h"
#include "fuzzer.h"

int main(int argc, char** argv){
	if(argc < 2)
	{
		printf("Usage: ./fuzzer num_iterations\n");
		fflush(stdout);
	}
	else
	{
		char* num_iterations_arg = argv[1];
		int num_iterations = atoi(num_iterations_arg);
		if(num_iterations < 1)
		{
			openTemplate();
			copyTemplate();
			// printf("Value is: %d\n", val);
			closeTemplate();
		}
		else
		{
			openTemplate();
			readTemplate();
			char* buffer = getBuffer();
			seedRand();

			int i;
			for(i = 0; i < num_iterations; i++)
			{
				fuzz(buffer);
			}
			
			writeOutput();
			freeBuffer();
			closeTemplate();
		}

	}

	return 0;
}