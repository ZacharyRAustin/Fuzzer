#include "FileManager.h"
#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>

#define TEMPLATE_NAME "template.txt"
#define OUTPUT_NAME "output.txt"

FILE* fd;

int openTemplate(){
	fd = fopen(TEMPLATE_NAME, "r");
	
	if(fd == NULL)
	{
		printf("Could not open file\n");
		return FILE_NOT_FOUND;
	}

	return 0;
}

int readTemplate(){
	return -1;
}

int writeOutput(){
	return -1;
}

int closeTemplate(){
	int check = -1;

	if(fd != NULL)
	{
		check = fclose(fd);
	}

	if(check == 0)
	{
		return 0;
	}

	return UNABLE_TO_CLOSE;
	
}