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
void read_text(FILE *file,text *text, wchar_t **text_str);
void describe_line(text *text, wchar_t *start_of_line, int *line_size, int *dedicated_lines, int *number_of_line);
//substring read_string_in_file(FILE *file);

#endif