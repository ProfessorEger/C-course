#include "free-string-list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <wchar.h>

string_buffer initialize_string_buffer(int number_of_strings, int string_size)
{
	string_buffer sb;

    // TODO: designated initializers?
	sb.number_of_strings = number_of_strings;
	sb.string_size = string_size;

    // NOTE: It's actually usually not a very good idea to use
    //       dynamic memory allocation in error handling, because
    //       memory allocation can itself fail, and then you'll
    //       be left without error handling.


    // The simplest way to achive this is to do:
    // struct string_buffer {
    //     string_... buffer[1024]; // ...
    // };

    // A bit harder ones if you wan't to have ability to create 
    // differently sized string_buffers:

    // 1. -----------------------------------------------------

    // struct string_buffer {
    //     string_...* buffer; // This is called flexible array
    // };

    // char buffer[...];
    // string_buffer = { ... = buffer };

    // 2. -----------------------------------------------------

    // struct string_buffer {
    //     string_... buffer[];
    //     // This is called^^ flexible array (you can look it up)
    // };

    // char buffer_for_string_buffer[size]; // alloca is the same as...
    // string_buffer *buffer = alloca(sizeof(string_buffer) + string_... * size);

    // 3. -----------------------------------------------------

    // #define create_string_buffer(size)                              \
    //     struct string_buffer_##size {                               \
    //         string_... buffer[size];                                \
    //     };                                                          \
    // 
    // #define string_buffer(size) string_buffer_##size 

    // You get the drill...

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
		wprintf(L"%s\n", current_str->string);
		current_str = current_str->next;
	}
}

int return_string_code(string_buffer *sb)
{
	return sb->first_string->code;
}
