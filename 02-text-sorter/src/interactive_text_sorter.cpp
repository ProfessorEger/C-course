#include "interactive_text_sorter.h"
#include <wchar.h>

bool handle_input_argument(int argc, char *argv[], string_buffer *error_buffer)
{
	char error_message[error_buffer->string_size];

	if(argc > 2)
		return true;
	else if(argc == 2)
		snprintf(error_message, sizeof(error_message) - sizeof(char), "textsorter: missing destination file operand after '%s'", argv[1]);
	else
		snprintf(error_message, sizeof(error_message) - sizeof(char), "textsorter: missing file operand");

	add_string(error_buffer, error_message);
	return false;
}

void print_in_file(FILE *file, text *text)
{
	if(text->text_array == NULL || file == NULL)
		return;
	for (int i=0;i < (*text).number_of_strings; i++)
		fwprintf(file, L"%ls\n", (*text).text_array[i].line);
}