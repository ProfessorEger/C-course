#include "read-file.h"
#include <wchar.h>
#include <stdlib.h>
#include <sys/stat.h>

void print_text(wchar_t **text_str)
{
	wprintf(L"\n1:\n%ls", *text_str);
}

void read_file(wchar_t **text_str, text *text, char *file_name)
{

	FILE *source_file = fopen(file_name, "r");
	allocate_memory_for_file(file_name, text_str);
	read_text(source_file, text, text_str);
	print_text(text_str);
}

unsigned allocate_memory_for_file(char *file_name, wchar_t **text_str)
{
	struct stat file_stat;
	if (stat(file_name, &file_stat) < 0)
		return 0;
	*text_str = (wchar_t *)malloc((file_stat.st_size + 1) * sizeof(wchar_t));
	return file_stat.st_size / sizeof(wchar_t);
}

void read_text(FILE *file, text *text, wchar_t **text_str)
{
	int i = 0;
	int number_of_line = 0;
	int line_size = 0;
	int dedicated_lines = 8;

	(*text).text_array = (substring *)malloc(dedicated_lines * sizeof(substring));
	(*text).text_array[number_of_line].line = &(*text_str)[i];

	while (!feof(file))
	{
		line_size++;
		fwscanf(file, L"%lc", &(*text_str)[i]);
		if ((*text_str)[i] == '\n' || feof(file))
			describe_line(&(*text), text_str[i] , &line_size, &dedicated_lines, &number_of_line);
		i++;
	}
	(*text_str)[i] = L'\0';
	*text_str = (wchar_t *)realloc(*text_str, (i + 1) * sizeof(wchar_t));
	(*text).number_of_strings = number_of_line;
}

void describe_line(text *text, wchar_t *start_of_line, int *line_size, int *dedicated_lines, int *number_of_line)
{
	if (dedicated_lines <= number_of_line + 1)
	{
		*dedicated_lines = *dedicated_lines * 2;
		(*text).text_array = (substring *)realloc((*text).text_array, *dedicated_lines * sizeof(substring));
	}
	(*text).text_array[*number_of_line].line_number = *number_of_line + 1;
	(*text).text_array[*number_of_line].line_size = *line_size;
	(*text).text_array[*number_of_line].line = start_of_line;
	*number_of_line++;
	*line_size = 0;
}

//*******************Старый код***********************

/*FILE *open_file(const char *file_name)
{
	FILE *file = fopen(file_name, "r");
	if (file == NULL)
		return NULL;
	return file;
}

void read_file(text *text, FILE *file)
{
	int number_of_lines = 0;
	int dedicated_lines = 1;
	while (!feof(file))
	{
		number_of_lines++;
		if (dedicated_lines <= number_of_lines)
		{
			dedicated_lines = dedicated_lines * 2;
			(*text).text_array = (substring *)realloc((*text).text_array, dedicated_lines * sizeof(substring));
		}
		(*text).text_array[number_of_lines - 1] = read_string_in_file(file);
		(*text).text_array[number_of_lines - 1].string_number = number_of_lines;
	}
	fclose(file);
	(*text).number_of_strings = number_of_lines;

	if (dedicated_lines > number_of_lines)
		(*text).text_array = (substring *)realloc((*text).text_array, number_of_lines * sizeof(substring));
}

substring read_string_in_file(FILE *file)
{
	int number_of_char = 0;
	int string_size = 8;
	wchar_t buffer_char = '\0';
	wchar_t *str = (wchar_t *)malloc(string_size * sizeof(wchar_t)); //лучше записывать в substring?
	while (buffer_char != L'\n' && !feof(file))
	{
		if (string_size <= (number_of_char + 1))
		{
			string_size = string_size * 2;
			str = (wchar_t *)realloc(str, string_size * sizeof(wchar_t));
		}

		fwscanf(file, L"%lc", &buffer_char);
		if (buffer_char == L'\n' || feof(file))
			break;

		str[number_of_char] = buffer_char;
		number_of_char++;
	}
	str[number_of_char] = L'\0';
	str = (wchar_t *)realloc(str, (number_of_char + 1) * sizeof(wchar_t));
	substring sub = {.string_size = number_of_char, .dynamic_string = str};

	return sub;
}*/
