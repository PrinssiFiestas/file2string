# File2String

A minimalist C library to read a file and store it to a string. Why? Because such a trivial task should only require a single line of code. 

## Example Program

```c
#include <stdio.h>
#include <stdlib.h>

#include "file2string.h"

int main()
{
	// Stack allocated fileContents
	{
		char* fileContents = readFile("exampleFile.txt");
		printf("%s\n", fileContents);
	}

	// Heap allocated fileContents
	{
		char* fileContents = mallocAndReadFile("exampleFile.txt");
		printf("%s\n", fileContents);
		free(fileContents);
	}

	// String buffer provided by user
	{
		char fileContents[sizeOfFile("exampleFile.txt")];
		readFileToStr("exampleFile.txt", fileContents);
		printf("%s\n", fileContents);
	}

	return 0;
}

```
