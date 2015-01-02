#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileManager.h"
#include "definitions.h"
#include "buffer.h"

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
		int curMaxSize = INIT_BUFFER_SIZE;
		char* buffer = getNewBuffer(curMaxSize);
		if(buffer == NULL)
		{
			return getErrorNum();
		}
		int c;
		int cnt = 0;

		while((c = fgetc(fd)) != EOF)
		{
			if(cnt == curMaxSize - 1)
			{
				buffer = getNewBufferAndCopy(curMaxSize * 2);
				if(buffer == NULL)
				{
					return getErrorNum();
				}
				curMaxSize = getNumberCharsAvail();
			}

			buffer[cnt] = (char) c;

			cnt++;
		}
		return getNumberCharsUsed();
	}

	return UNABLE_TO_READ_TEMPLATE;
} 

/*
 * Write the buffer to the output file
 * If the write was successful, return the number of characters written
 * Return UNABLE_TO_WRITE_OUTPUT otherwise
 */
int writeOutput(){
	FILE* out = fopen(OUTPUT_NAME, "w");
	char* buffer = getBufferStart();
	if(buffer == NULL)
	{
		return getErrorNum();
	}
	if(out != NULL)
	{
		int i;
		int bufSize = getNumberCharsUsed();
		if(bufSize < 0)
		{
			return getErrorNum();
		}
		for(i = 0; i < bufSize; i++)
		{
			int writeCheck = fputc(buffer[i], out);
			if(writeCheck == EOF && i != bufSize)
			{
				fclose(out);
				return UNABLE_TO_WRITE_OUTPUT;
			}
		}

		// fputc(EOF, out);
		fclose(out);
		return i;
	}

	fclose(out);

	return UNABLE_TO_WRITE_OUTPUT;
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

/*
 * Copy the template to the output file
 * Uses fgetc because it is part of the standard C library and therefore portable
 * If the copy is successful, return the number of characters written
 * If the template is not open, return UNABLE_TO_READ_TEMPLATE
 * If the output file can't be opened, return UNABLE_TO_OPEN_OUTPUT
 * if the number of characters read != number of characters written. return UNEQUAL_CHARACTER_COUNT
 */
int copyTemplate(){
	if(fd != NULL)
	{
		FILE* out = fopen(OUTPUT_NAME, "w");
		if(out != NULL)
		{
			int read = 0; 
			int written = 0;
			int val;

			while((val = fgetc(fd)) != EOF)
			{
				int writeCheck = fputc((char) val, out);
				read++;
				if(writeCheck == val)
				{
					written++;
				}
			}

			fclose(out);

			if(written == read)
			{
				return written;
			}
			else
			{
				return UNEQUAL_CHARACTER_COUNT;
			}
		}
		else
		{
			return UNABLE_TO_OPEN_OUTPUT;
		}
	}

	return UNABLE_TO_READ_TEMPLATE;
}