#include <stdio.h>
#include "FileManager.h"

int main(int argc, char** argv){
	if(argc < 2)
	{
		printf("Usage: ./fuzzer num_iterations\n");
		fflush(stdout);
	}
	else
	{
		int val = readTemplate();
		printf("Value is: %d\n", val);
	}

	return 0;
}