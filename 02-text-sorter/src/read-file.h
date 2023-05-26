#ifndef READ_FILE_H
#define READ_FILE_H

#include <stdio.h>

typedef struct substring
{
	int string_size;
	wchar_t *dynamic_string;
	int string_number;
} substring;

typedef struct text
{
	substring *text_array;
	int number_of_string;
}text;

FILE *open_file(const char *file_name);
void read_file(text *text, FILE *file);
substring read_string_in_file(FILE *file);

#endif