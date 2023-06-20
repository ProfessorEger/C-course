#include "read-file.h"
#include <wchar.h>
#include <stdlib.h>
#include <sys/stat.h>

void read_file(wchar_t **text_str, text *text, char *file_name)
{

	FILE *source_file = fopen(file_name, "r");
	allocate_memory_for_file(file_name, text_str);
	read_text(source_file, text_str);
	split_into_lines(text, text_str);
}

unsigned allocate_memory_for_file(char *file_name, wchar_t **text_str)
{
	struct stat file_stat;
	if (stat(file_name, &file_stat) < 0)
		return 0;
	*text_str = (wchar_t *)malloc((file_stat.st_size + 1) * sizeof(wchar_t));
	return file_stat.st_size / sizeof(wchar_t);
}

void read_text(FILE *file, wchar_t **text_str)
{
	int i = 0;

	while (!feof(file))
	{
		fwscanf(file, L"%lc", &(*text_str)[i]);
		i++;
	}
	(*text_str)[i] = L'\0';
	*text_str = (wchar_t *)realloc(*text_str, (i + 1) * sizeof(wchar_t));
}

void split_into_lines(text *text, wchar_t **text_str)
{
	int line_number = 0;
	int line_size = 0;
	wchar_t *pointer_to_line = *text_str;

	int dedicated_lines = 64;
	(*text).text_array = (substring *)malloc(dedicated_lines * sizeof(substring));

	for(int i = 0;;i++)
	{
		if (*pointer_to_line == '\n' || *pointer_to_line == '\0')
		{
			if(line_number + 1 >= dedicated_lines)
			{
				dedicated_lines = dedicated_lines * 2;
				(*text).text_array = (substring *)realloc((*text).text_array, dedicated_lines * sizeof(substring));
			}

			(*text).text_array[line_number].line = pointer_to_line - line_size;
			(*text).text_array[line_number].line_number = line_number + 1;
			(*text).text_array[line_number].line_size = line_size;
			line_number++;
			line_size = 0;

			if(*pointer_to_line == '\0')
			{
				(*text).number_of_strings = line_number;
				(*text).text_array = (substring *)realloc((*text).text_array, line_number * sizeof(substring));
				return;
			}

			(*text_str)[i] = L'\0';
		}
		else
			line_size++;
		
		pointer_to_line++;
	}
}