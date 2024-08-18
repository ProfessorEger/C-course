#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>


#define READ_INPUT(scan_fmt, put_str, num_args, ...) 		\
while(1) {																\
	int input_check = scanf(scan_fmt, __VA_ARGS__);			\
	char check_char = '\0';											\
	while (scanf("%c", &check_char), check_char != '\n')	\
	{																		\
		if (!isblank(check_char))									\
			input_check = 0;											\
	}																		\
	if (input_check == num_args)									\
		break;															\
	puts(put_str);														\
}