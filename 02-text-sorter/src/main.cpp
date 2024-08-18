#include "read-file.h"
#include "interactive_text_sorter.h"
#include "text-transformer.h"
#include "free-string-list.h"
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "en_US.UTF-8");

	error_buffer *err_buffer = (error_buffer *)alloca(find_string_buffer_size(6, 250));
	initialize_string_buffer(err_buffer, 6, 250);

	if (!handle_input_argument(argc, argv, err_buffer))
	{
		print_string_buffer(err_buffer);
		return return_string_code(err_buffer);
	}

	char *source_file_name = argv[1];
	char *finished_file_name = argv[2];

	wchar_t *text_str = NULL;
	text source_text = {.text_array = NULL, .number_of_strings = 0};
	read_file(&text_str, &source_text, source_file_name, err_buffer);

	FILE *finished_file = my_fopen(finished_file_name, "w", err_buffer);

	sort_text_array(&source_text);
	print_in_file(finished_file, &source_text);

	reverse_substrings_in_text(&source_text);
	sort_text_array(&source_text);
	reverse_substrings_in_text(&source_text);
	print_in_file(finished_file, &source_text);

	return_original(&source_text); // TODO: naming, restore_*?
	print_in_file(finished_file, &source_text);

	if (finished_file != NULL)
		fclose(finished_file);
	free(text_str);
	free(source_text.text_array);

	print_string_buffer(err_buffer);

	return return_string_code(err_buffer);
}
