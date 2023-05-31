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

void retutn_original(text *text) // Задача о 100 заключенных
{
	qsort((*text).text_array, (*text).number_of_strings, sizeof(substring), return_compare_substring);
}

int return_compare_substring(const void *a, const void *b)
{
	const substring *substring_a = (const substring *)a;
	const substring *substring_b = (const substring *)b;

	return (*substring_a).string_number - (*substring_b).string_number;
}

