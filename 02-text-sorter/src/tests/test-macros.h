#include "ansi-colors.h"
#include <stdio.h>

// TODO: It's better to wrap macros in do...while(0)
#define TEST_FUNC_PTR(test_number, func, func_cmpr, ptr, expected, ...)      \
	func(__VA_ARGS__);		                                                 \
	if (func_cmpr(*ptr, expected) != 0)                                      \
		printf("Test №%d " TEXT_RED("failed:") " %s\n", test_number, #func); \
	else                                                                     \
		printf("Test №%d " TEXT_GREEN("passed:") " %s\n", test_number, #func);

