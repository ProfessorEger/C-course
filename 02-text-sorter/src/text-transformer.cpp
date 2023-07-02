#include "text-transformer.h"
#include <stdlib.h>
#include <string.h>

void sort_text_array(text *text)
{
	if(text->text_array == NULL)
		return;
	qsort((*text).text_array, (*text).number_of_strings, sizeof(substring), compare_substring);

    // TODO: write your own sort :)

    // Every CS student ever has to write sort algorithm at least once in a lifetime. 
    // If you haven't written sort in your career as a programmer, than you are a
    // phony. No way around it, just have to do it.

    // That's a price of admission.

    // I recommend you to write quick sort, as it's very theoretical, beautiful and
    // fast at the same time. There are also a lot of ways to improve it for small, 
    // and medium size arrays, even lectures about it.

    // There also ways to combat worst cases for quick sorts which are implemented 
    // in standard library, and I will tell you when you'll have your implementation :)
}

int compare_substring(const void *a, const void *b)
{
	const substring *substring_a = (const substring *)a;
	const substring *substring_b = (const substring *)b;

	for (int i = 0; i < (*substring_a).line_size && i < (*substring_b).line_size; i++)
	{
		if ((*substring_a).line[i] != (*substring_b).line[i])
			return (*substring_a).line[i] - (*substring_b).line[i];
	}

	return 0; // TODO: What if one string is substring of the other?
              //       They are not really equal.
}

void reverse_substrings_in_text(text *text)
{
	if(text->text_array == NULL)
		return;
	for (int i = 0; i <= (*text).number_of_strings; i++)
		reverse_substring(&(*text).text_array[i]);
}

void reverse_substring(substring *substring)
{
	wchar_t buffer_char = '\0';
	for (int j = 0; j < (double((*substring).line_size)) / 2 && (*substring).line[j] != '\0'; j++)
	{ // TODO: I see no ^^^^^^^^ reason to cast to double here, where integer division would do
		buffer_char = (*substring).line[j];
		(*substring).line[j] = (*substring).line[(*substring).line_size - 1 - j];
		(*substring).line[(*substring).line_size - 1 - j] = buffer_char;

        // TODO: extract, make "swap" function, this will be useful when you'll 
        //       write your own sort, too.
	}
}

void return_original(text *text)
{
	if(text->text_array == NULL)
		return;
	substring buffer_substring = (*text).text_array[0];
	for (int i = 0; i < (*text).number_of_strings; i++)
	{
		while ((*text).text_array[i].line_number - 1 != i)
		{ // TODO: I think it would be more readable if you'd use line_numbers from 0
			buffer_substring = (*text).text_array[i];
			(*text).text_array[i] = (*text).text_array[buffer_substring.line_number - 1];
			(*text).text_array[buffer_substring.line_number - 1] = buffer_substring;

            // TODO: see, this is "swap" too! 
		}
	}
}
