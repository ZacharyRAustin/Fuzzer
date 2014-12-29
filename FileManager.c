#include "FileManager.h"
#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definitions==========================================
#define TEMPLATE_NAME "template.txt"
#define OUTPUT_NAME "output.txt"
#define INIT_BUFFER_SIZE 256

//class vars===========================================
FILE* fd;

//function prototypes==================================
void printBuf(char*);

//functions============================================
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

void printBuf(char* buf){
	printf("%s\n", buf);
	fflush(stdout);
}