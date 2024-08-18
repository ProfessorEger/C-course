#ifndef UNIVERSAL_UNIT_TEST_H
#define UNIVERSAL_UNIT_TEST_H

#include "ansi-colors.h"

#define TEST_FUNC(test_number, func, func_cmpr, expected_return_value, ...)			\
	do {																			\
		if (func_cmpr(func(__VA_ARGS__), expected_return_value) != 0)				\
			printf("Test №%d " TEXT_RED("failed:") " %s\n", test_number, #func);	\
		else																		\
			printf("Test №%d " TEXT_GREEN("passed:") " %s\n", test_number, #func);	\
	} while(0)

#endif