#include "free-string-list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

string_buffer initialize_string_buffer(int number_of_strings, int string_size)
{
	string_buffer sb;
	sb.number_of_strings = number_of_strings;
	sb.string_size = string_size;
	sb.buffer = (char *)malloc(number_of_strings * string_size * sizeof(char));
	sb.info = (string_info *)malloc(number_of_strings * sizeof(string_info));

	for (int i = 0; i < number_of_strings; i++)
	{
		sb.info[i].string = sb.buffer + i * string_size;
		sb.info[i].code = NULL_CODE;
		sb.info[i].string_is_busy = false;
		sb.info[i].next = (i < number_of_strings - 1) ? &sb.info[i + 1] : NULL;
		sb.info[i].prev = (i > 0) ? &sb.info[i - 1] : NULL;
	}
	sb.first_string = &sb.info[0];
	sb.closing_string = &sb.info[number_of_strings - 1];

	return sb;
}

void add_string(string_buffer *sb, char *new_string, int code)
{
	string_info *current_str = sb->first_string;
	for (int i = 0; i < sb->number_of_strings; i++)
	{
		if (current_str->string_is_busy)
		{
			if (i >= sb->number_of_strings - 1)
				break;
			current_str = current_str->next;
		}
		else
		{
			strncpy(current_str->string, new_string, sb->string_size);
			current_str->string_is_busy = true;
			current_str->code = code;
			break;
		}
	}
}

void remove_string(string_buffer *sb, char *unnecessary_string, int code)
{
	for (int i = 0; i < sb->number_of_strings; i++)
	{
		if (!sb->info[i].string_is_busy || (strcmp(sb->info[i].string, unnecessary_string) != 0 && unnecessary_string != NULL) || (sb->info[i].code != code && code != NULL_CODE))
			continue;

		sb->info[i].string_is_busy = false;

		if (&sb->info[i] != sb->first_string) // убрает строку, ставя взаимные указатели на соседних строках
			sb->info[i].prev->next = sb->info[i].next;
		else
			sb->first_string = sb->info[i].next;
		if (&sb->info[i] != sb->closing_string)
			sb->info[i].next->prev = sb->info[i].prev;
		else
			sb->closing_string = sb->info[i].prev;

		sb->closing_string->next = &sb->info[i]; // ставит строку на последнее место
		sb->info[i].prev = sb->closing_string;
		sb->info[i].next = NULL;
		sb->closing_string = &sb->info[i];
	}
}

void print_string_buffer(string_buffer *sb)
{
	string_info *current_str = sb->first_string;
	while (current_str != NULL)
	{
		if (!current_str->string_is_busy)
			break;
		printf("%s\n", current_str->string);
		current_str = current_str->next;
	}
}

int return_string_code(string_buffer *sb)
{
	return sb->first_string->code;
}