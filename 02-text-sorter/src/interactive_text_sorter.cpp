#include "interactive_text_sorter.h"
#include <wchar.h>

bool handle_input_argument(int argc, char *argv[], string_buffer *error_buffer)
{
	char error_message[STRING_BUFFER_STRING_SIZE]; // VLA Variable Length Array
    // TODO: it's better to be cautios when using VLAs cause they
    //       can become whatever size and possibly overflow stack

    // Even if it's safe in this case, it's better to somehow make it obvious 
    // for programmer reading.

	if(argc > 2)
		return true; // TODO: else after return is considered a bad style :/
	else if(argc == 2)
		snprintf(error_message, sizeof(error_message) - sizeof(char), "textsorter: missing destination file operand after '%s'", argv[1]);
	else
		snprintf(error_message, sizeof(error_message) - sizeof(char), "textsorter: missing file operand");
    // TODO:                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ you can calculate 
    //       this once and use a thing called "variable" to store the result :/

	add_string(error_buffer, error_message, 22);
	return false;
}

void print_in_file(FILE *file, text *text)
{
	if(text->text_array == NULL || file == NULL)
		return;

	for (int i = 0;i < (*text).number_of_strings; i++)
		fwprintf(file, L"%ls\n", (*text).text_array[i].line);
}
