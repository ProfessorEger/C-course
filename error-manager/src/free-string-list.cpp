#include "free-string-list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

string_buffer sb;

string_buffer *initialize_string_buffer()
{
	for(int i = 0; i < STRING_BUFFER_NUMBER_OF_STRINGS; i++)
	{
		sb.buffer[i].next = (i < STRING_BUFFER_NUMBER_OF_STRINGS - 1)? &sb.buffer[i+1] : NULL;
		sb.buffer[i].prev = (i > 0)? &sb.buffer[i-1] : NULL;
		sb.buffer[i].string_is_busy = false;
	}

	sb.first_string = &sb.buffer[0];
	sb.current_string = sb.first_string;
	sb.closing_string = &sb.buffer[STRING_BUFFER_NUMBER_OF_STRINGS - 1];
	
	return &sb;
}

void add_string(string_buffer *sb, char *new_string, int code)
{
	if(sb->current_string->string_is_busy)
		return;

	strncpy(sb->current_string->string, new_string, STRING_BUFFER_STRING_SIZE);
	sb->current_string->string[STRING_BUFFER_STRING_SIZE] = '\0';
	sb->current_string->code = code;
	sb->current_string->string_is_busy = true;

	sb->current_string = (sb->current_string != sb->closing_string)? sb->current_string->next : sb->current_string;
}

void remove_string(string_buffer *sb, char *unnecessary_string, int code)
{
	string_info *current_str = sb->first_string;
	for(int i = 0; i < STRING_BUFFER_NUMBER_OF_STRINGS; i++)
	{
		if(current_str == NULL || !current_str->string_is_busy)
			break;

		if ((strcmp(current_str->string, unnecessary_string) != 0 && unnecessary_string != NULL) || (current_str->code != code && code != STRING_BUFFER_NULL_CODE))
			{
				current_str = current_str->next;
				continue;
			}

		current_str->string_is_busy = false;
		if (current_str == sb->closing_string)
			break;

		string_info *next_str = current_str->next; //запоминаем следующую строку, поскольку дальше будем менять current_str->next
		
		current_str->next->prev = current_str->prev; ////достаем строку из списка
		if(current_str != sb->first_string)
			current_str->prev->next = current_str->next;

		current_str->prev = sb->closing_string; // ставим ее в конец
		current_str->next = NULL;
		sb->closing_string->next = current_str;
		sb->closing_string = current_str;

		if (current_str == sb->first_string)
			sb->first_string = next_str;

		sb->first_string = (sb->first_string == current_str)? next_str : sb->first_string;
		current_str = next_str;
	}

	//пересчет текущей строки в связи с перестановками
	sb->current_string = (sb->current_string->string_is_busy && sb->current_string != sb->closing_string)? sb->current_string->next : sb->current_string;
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