#include "read-file.h"
#include "interactive_text_sorter.h"
#include "text-transformer.h"
#include <locale.h>
#include <wchar.h>

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "en_US.UTF-8");

	if(!handle_input_argument(argc, argv))
		return 1;
	char *source_file_name = argv[1];
	FILE *source_file = open_file(source_file_name);
	print_opening_file_result (source_file, argv);
	if (source_file == NULL) 
		return 1;
	
	text source_text = {.text_array = NULL, .number_of_strings = 0};
	read_file(&source_text, source_file);

	print_text_array(0, &source_text);

	sort_text_array(&source_text);
	print_text_array(1, &source_text);
	
	reverse_substrings_in_text(&source_text);
	sort_text_array(&source_text);
	reverse_substrings_in_text(&source_text);
	print_text_array(2, &source_text);

	retutn_original(&source_text);
	print_text_array(0, &source_text);

	return 0;
}