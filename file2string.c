#include <stdio.h>
#include <stdlib.h>

#include "file2string.h"

static FILE* fopenWithErrorHandling(const char* filePath, const char* sourceFile, int line)
{
	// Suppres unused parameter warnings
	(void)(sourceFile); (void)(line);

	FILE* file;

	// At the time of writing MSVC requires fopen_s for whatever reason
#if defined(_MSC_VER) && (_MSC_VER >= 1400 ) && (!defined WINCE)
	int err = fopen_s(&file, filePath, "r");
	if(err)
#else
	file = fopen(filePath, "r");
	if(file == NULL)
#endif
	{
#ifdef PRINT_FILE_OPENING_FAILURE_MESSAGE_TO_STDOUT
		printf("Error opening file \"%s\" on \"%s\" line %i!\n", filePath, sourceFile, line);
#endif
#ifdef EXIT_ON_FILE_OPENING_FAILURE
		exit(EXIT_FAILURE);
#endif
	}
	return file;
}

long _sizeOfFile(const char* filePath, const char* sourceFile, int line)
{
	FILE* file = fopenWithErrorHandling(filePath, sourceFile, line);
	if(file == NULL)
		return -1;

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fclose(file);
	
	return fileSize + 1/*null termination*/;
}

char* _readFileToStr(const char* filePath, char* outputStr, const char* sourceFile, int line)
{
	FILE* file = fopenWithErrorHandling(filePath, sourceFile, line);
	if(file == NULL)
		return NULL;

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	fread(outputStr, fileSize, 1, file);
	outputStr[fileSize] = '\0';
	fclose(file);

	return outputStr;
}

char* _mallocAndReadFile(const char* filePath, const char* sourceFile, int line)
{
	FILE* file = fopenWithErrorHandling(filePath, sourceFile, line);
	if(file == NULL)
		return NULL;

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* fileContents = (char*)malloc(fileSize * sizeof(char));
	fread(fileContents, fileSize, 1, file);
	fileContents[fileSize] = '\0';
	fclose(file);
	
	return fileContents;
}

