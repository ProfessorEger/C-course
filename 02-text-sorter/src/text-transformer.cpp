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

	for (int i = 0; i < (*substring_a).string_size || i < (*substring_b).string_size; i++)
	{
		if ((*substring_a).dynamic_string[i] != (*substring_b).dynamic_string[i])
			return (*substring_a).dynamic_string[i] - (*substring_b).dynamic_string[i];
	}

	return 0;
}