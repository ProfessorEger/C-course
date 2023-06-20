#ifndef READ_FILE_H
#define READ_FILE_H

#include <stdio.h>

typedef struct substring
{
	int line_size;
	wchar_t *line;
	int line_number;
} substring;

typedef struct text
{
	substring *text_array;
	int number_of_strings;
}text;

void read_file(wchar_t **text_str, text *text, char *file_name);
unsigned allocate_memory_for_file(char *file_name, wchar_t **text_str);
void read_text(FILE *file, wchar_t **text_str);
void split_into_lines(text *text, wchar_t **text_str);

#endif