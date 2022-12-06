#ifndef FILE2STRING_H
#define FILE2STRING_H

// ------------------------------------
// Settings

//#define PRINT_FILE_OPENING_FAILURE_MESSAGE_TO_STDOUT
//#define EXIT_ON_FILE_OPENING_FAILURE

// ------------------------------------

#define readFile(FILE_PATH)	\
	readFileToStr(FILE_PATH, (char*)alloca(sizeOfFile(FILE_PATH)))

#define sizeOfFile(FILE_PATH)	\
	_sizeOfFile(FILE_PATH, __FILE__, __LINE__)

#define readFileToStr(FILE_PATH, OUTPUT_STR)	\
	_readFileToStr(FILE_PATH, OUTPUT_STR, __FILE__, __LINE__)

#define mallocAndReadFile(FILE_PATH)	\
	_mallocAndReadFile(FILE_PATH, __FILE__, __LINE__)

#ifdef __cplusplus
extern "C" {
#endif

// Returns -1 on failure
long _sizeOfFile(const char* filePath, const char* sourceFile, int line);

// Returns NULL on failure
char* _readFileToStr(const char* filePath, char* outputString, const char* sourceFile, int line);

// Returns NULL on failure
char* _mallocAndReadFile(const char* filePath, const char* sourceFile, int line);

// ------------------------------------

#ifdef __cplusplus
}
#endif // extern "C"

// Get rid of ALE linter error
#if defined(__GNUC__) && !defined(alloca)
	#define alloca(size)   __builtin_alloca (size)
#endif

#endif // FILE2STRING_H

