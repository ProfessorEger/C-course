#include "text-transformer.h"
#include <stdlib.h>
#include <string.h>

void sort_text_array(text *text)
{
	qsort((*text).text_array, (*text).number_of_strings, sizeof(substring), compare_substring);
}

int compare_substring(const void *a, const void *b)
{
	const substring *substring_a = (const substring *)a;
	const substring *substring_b = (const substring *)b;

	for (int i = 0; i < (*substring_a).string_size && i < (*substring_b).string_size; i++)
	{
		if ((*substring_a).dynamic_string[i] != (*substring_b).dynamic_string[i])
			return (*substring_a).dynamic_string[i] - (*substring_b).dynamic_string[i];
	}

	return 0;
}

void reverse_substrings_in_text(text *text)
{
	for (int i = 0; i <= (*text).number_of_strings; i++)
		reverse_substring(&(*text).text_array[i]);
}

void reverse_substring(substring *substring)
{
	wchar_t buffer_char = '\0';
	for (int j = 0; j < (double((*substring).string_size)) / 2 && (*substring).dynamic_string[j] != '\0'; j++)
	{
		buffer_char = (*substring).dynamic_string[j];
		(*substring).dynamic_string[j] = (*substring).dynamic_string[(*substring).string_size - 1 - j];
		(*substring).dynamic_string[(*substring).string_size - 1 - j] = buffer_char;
	}
}

void return_original(text *text) // Задача о 100 заключенных
{
	substring buffer_substring = (*text).text_array[0];
	for (int i = 0; i < (*text).number_of_strings; i++)
	{
		while ((*text).text_array[i].string_number - 1 != i)
		{
			buffer_substring = (*text).text_array[i];
			(*text).text_array[i] = (*text).text_array[buffer_substring.string_number - 1];
			(*text).text_array[buffer_substring.string_number - 1] = buffer_substring;
		}
	}
}