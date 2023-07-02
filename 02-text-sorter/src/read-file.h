#ifndef READ_FILE_H
#define READ_FILE_H

#include "free-string-list.h"
#include <stdio.h>

//                    +---------+
// TODO: docs "_" x_x | 0_x_x_0 |
//                    |         |
//                    |  _____  |
//                    +---------+

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

void read_file(wchar_t **text_str, text *text, char *file_name, string_buffer *error_buffer);

// TODO: use better naming, guarded_fopen... (or come up with a good name yourself)
FILE *my_fopen(const char *filename, const char *mode, string_buffer *error_buffer);
void allocate_memory_for_file(char *file_name, wchar_t **text_str, string_buffer *error_buffer);
void read_text(FILE *file, wchar_t **text_str, string_buffer *error_buffer);
void split_into_lines(text *text, wchar_t **text_str);

#endif
