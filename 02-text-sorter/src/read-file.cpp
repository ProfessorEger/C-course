#include "read-file.h"
#include <wchar.h>
#include <stdlib.h>
#include <sys/stat.h>

void read_file(wchar_t **text_str, text *text, char *file_name, string_buffer *error_buffer)
{
	FILE *source_file = my_fopen(file_name, "r", error_buffer);
	allocate_memory_for_file(file_name, text_str, error_buffer);
	read_text(source_file, text_str, error_buffer);
	if(source_file != NULL)
		fclose(source_file);
	split_into_lines(text, text_str);
}

FILE *my_fopen(const char *file_name, const char *mode, string_buffer *error_buffer)
{

	FILE *source_file = fopen(file_name, mode);
	if(source_file != NULL)
		return source_file;
	
	char error_message[error_buffer->string_size];
	snprintf(error_message, sizeof(error_message) - sizeof(char), "textsorter: cannot stat '%s': Unable to open file", file_name);
	add_string(error_buffer, error_message, 2);
	return source_file;
}

void allocate_memory_for_file(char *file_name, wchar_t **text_str, string_buffer *error_buffer)
{
	char error_message[error_buffer->string_size];
	struct stat file_stat; // TODO: extract (make file_size function)
	if (stat(file_name, &file_stat) != 0)
	{
		snprintf(error_message, sizeof(error_message) - sizeof(char), "textsorter: cannot stat '%s': No such file", file_name);
		add_string(error_buffer, error_message, 2);
	}
	else
		*text_str = (wchar_t *)malloc((file_stat.st_size + 1) * sizeof(wchar_t));
	if(text_str == NULL)
		add_string(error_buffer, "textsorter: failed to allocate memory", 12);
}

void read_text(FILE *file, wchar_t **text_str, string_buffer *error_buffer)
{
    // TODO: a common style is to use spaces after statement's names:
    //       so if (...) instead of if(...)

    // On the contrary, after function names spaces are not used foo(...),
    // but you seem to follow this guideline well.

	if(file == NULL)
		return;
	
	int i = 0;
	while (!feof(file))
	{
		fwscanf(file, L"%lc", &(*text_str)[i]);
		i++;
	}
	(*text_str)[i] = L'\0';
	*text_str = (wchar_t *)realloc(*text_str, (i + 1) * sizeof(wchar_t));

	if(text_str == NULL)
		add_string(error_buffer, "textsorter: failed to allocate memory", 12);
}

void split_into_lines(text *text, wchar_t **text_str)
{
	if(*text_str == NULL)
		return;

	int line_number = 0;
	int line_size = 0;
	wchar_t *pointer_to_line = *text_str;

	int dedicated_lines = 64;

    // TODO: it's faster, to just count number of lines, and
    //       only then allocate buffer, but correct size.
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

            // TODO: designated initializers? Meaning:
            // (*text).text_array[line_number] = {
            //     ...
            // };

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
