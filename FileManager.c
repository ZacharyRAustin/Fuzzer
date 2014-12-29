#include "FileManager.h"
#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definitions================================================================
#define TEMPLATE_NAME "template.txt"
#define OUTPUT_NAME "output.txt"
#define INIT_BUFFER_SIZE 256

//class vars=================================================================
FILE* fd;

//function prototypes========================================================
void printBuf(char*);

//functions==================================================================
/*
 * Open the file template file
 * Return 0 if file successfully opened
 * Return FILE_NOT_FOUND otherwise
 */
int openTemplate(){
	fd = fopen(TEMPLATE_NAME, "r");
	
	if(fd == NULL)
	{
		printf("Could not open file\n");
		return FILE_NOT_FOUND;
	}

	return 0;
}
 
/*
 * Read the template file into a buffer
 * Double buffer size when capacity is reached
 * If the file has been opened, return the number of characters in the buffer
 * Return UNABLE_TO_READ_TEMPLATE otherwise
 */
int readTemplate(){
	if(fd != NULL)
	{
		int curSize = INIT_BUFFER_SIZE;
		char* b = malloc(curSize * sizeof(char));
		int c;
		int cnt = 0;

		while((c = fgetc(fd)) != EOF)
		{
			if(cnt == curSize - 1)
			{
				int newSize = curSize * 2;
				char* temp = b;
				b = malloc(newSize * sizeof(char));
				memset(b, '\0', newSize * sizeof(char));
				memcpy(b, temp, curSize * sizeof(char));
				free(temp);
				curSize = newSize;
			}

			b[cnt] = (char) c;

			cnt++;
		}

		b[cnt] = '\0';

		int bufSize = strlen(b);
		free(b);
		return bufSize;
	}

	return UNABLE_TO_READ_TEMPLATE;
} 

/*
 * Write the buffer to the output file
 * If the write was successful, return the number of characters written
 * Return UNABLE_TO_WRITE_OUTPUT otherwise
 */
int writeOutput(){
	return -1;
}

/*
 * Close the template file
 * If the file was closed successfully, return 0
 * Return UNABLE_TO_CLOSE otherwise
 */
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

/*
 * Print the contents of the buffer to stdout
 */
void printBuf(char* buf){
	printf("%s\n", buf);
	fflush(stdout);
}