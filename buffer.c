#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "buffer.h"

//definitions===========================================================

//Typedefs==============================================================
typedef struct charBuffer_t{
	char* start;
	int size;
} charBufferT;

//global class vars=====================================================
charBufferT buffer;
int errno;

//function prototypes===================================================
char* setBuffer(char* newStart, int bufSize);

//functions=============================================================
/*
 * Initializes the fields of the buffer
 * Also resets the errno flag
 * Should be called before using any other functions
 * 
 * If the buffer is in use, it will be closed before being reinitialized
 */
 void initBuffer(){
 	if(buffer.start != NULL)
 	{
 		closeBuffer();
 	}
 	buffer.start = NULL;
 	buffer.size = -1;
 	errno = 0;
 }

/*
 * Sets the contents of the buffer type
 * Closes the current buffer, if it exists
 * 
 * Returns NULL and sets errno INVALID_ARGUMENTS if bufSize < 0 
 * or newStart invalid pointer
 * Returns pointer to the buffer otherwise
 */
 char* setBuffer(char* newStart, int bufSize){
 	if(bufSize < 0 || newStart == NULL || newStart <= 0)
 	{
 		errno = INVALID_ARGUMENTS;
 		return NULL;
 	}
 	if(buffer.start != NULL)
 	{
 		closeBuffer();
 	}
 	buffer.start = newStart;
 	buffer.size = bufSize;
 	return buffer.start;
 }

/*
 * Returns the start of the buffer if one exists
 * Returns NULL otherwise
 */
 char* getBufferStart(){
 	if(buffer.start != NULL)
 	{
 		errno = 0;
 		return buffer.start;
 	}
 	errno = NO_PREVIOUS_BUFFER;
 	return NULL;
 }

/*
 * Returns the size of the buffer if one exists
 * Returns -1 if no buffer is set;
 */
 int getBufferSize(){
 	errno = 0;
 	return buffer.size;
 }

/*
 * Releases the current buffer if it exists 
 * and reinitializes its values to the empty state
 */
 void closeBuffer(){
 	if(buffer.start != NULL)
 	{
 		memset(buffer.start, '\0', buffer.size * sizeof(char));
 		free(buffer.start);;
 	}

 	initBuffer();
 }

/*
 * Allocates a new buffer for the desired number of characters
 * New buffer characters set to '\0'
 * Updates buffer structure to reflect the changes 
 * Frees the buffer if one already exists
 *  
 * Returns NULL and sets errno to INVALID_ARGUMENTS 
 * if the number of characters is < 1
 *
 * Returns NULL and sets errno to UNABLE_TO_ALLOC if the call
 * to malloc fails
 *
 * Returns the pointer to the new Buffer if setBuffer is successful
 */
 char* getNewBuffer(int numCharacters){
 	errno = 0;
 	if(numCharacters < 1)
 	{
 		errno = INVALID_ARGUMENTS;
 		return NULL;
 	}

 	if(buffer.start != NULL)
 	{
 		closeBuffer();
 	}

 	char* temp = malloc(sizeof(char) * numCharacters);
 	if(temp == NULL)
 	{
 		errno = UNABLE_TO_ALLOC;
 		return NULL;
 	}

 	memset(temp, '\0', numCharacters * sizeof(char));

 	return setBuffer(temp, numCharacters);
 }

/*
 * Same function as above, but allows the contents of the buffer
 * that is being replaced to be copied over to the new buffer if
 * there is enough space
 *
 * Returns NULL and sets the errno to INVALID_ARGUMENTS if 
 * numCharacters is < 1
 *
 * Returns NULL and sets the errno to NOT_ENOUGH_BUFFER_SPACE if
 * the number of characters is less than the number from
 * the previous buffer
 *
 * Returns NULL and sets the errno to NO_PREVIOUS_BUFFER if 
 * there is no previous buffer
 *
 * Returns NULL and sets errno to UNABLE_TO_COPY_CONTENTS if
 * the buffers are not equal after copying
 *
 * Returns NULL and sets errno to UNABLE_TO_ALLOC if the call
 * to malloc fails
 * 
 * Returns the pointer to the new Buffer and sets the errno to 0 
 * otherwise
 */
 char* getNewBufferAndCopy(int numCharacters){
 	errno = 0;

 	//make sure numCharacters is valid
 	if(numCharacters < 1)
 	{
 		errno = INVALID_ARGUMENTS;
 		return NULL;
 	}

 	//check for previous buffer
 	if(buffer.start == NULL)
 	{
 		errno = NO_PREVIOUS_BUFFER;
 		return NULL;
 	}

	//check new bufsize is large enough
 	if(numCharacters < buffer.size)
 	{
 		errno = NOT_ENOUGH_BUFFER_SPACE;
 		return NULL;
 	}

 	char* temp = buffer.start;
 	int tempSize = buffer.size;

 	char* newBuf = malloc(sizeof(char) * numCharacters);

 	if(newBuf == NULL)
 	{
 		errno = UNABLE_TO_ALLOC;
 		return NULL;
 	}

 	memset(newBuf, '\0', sizeof(char) * numCharacters);

 	int i;
 	for(i = 0; i < tempSize; i++)
 	{
 		newBuf[i] = temp[i];
 	}

 	if(!strcmp(temp, newBuf))
 	{
 		errno = UNABLE_TO_COPY_CONTENTS;
 		free(newBuf);
 		return NULL;
 	}

 	closeBuffer();
 	return setBuffer(newBuf, numCharacters);
 }

/*
 * Returns the error number
 */
 int getErrorNum(){
 	return errno;
 }