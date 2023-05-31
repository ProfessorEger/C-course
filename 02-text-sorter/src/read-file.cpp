#include "read-file.h"
#include <wchar.h>
#include <stdlib.h>

FILE *open_file(const char *file_name)
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
}
