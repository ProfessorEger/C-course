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
	char *finished_file_name = argv[2];
/*	print_opening_file_result (source_file, argv);
	if (source_file == NULL) 
		return 1;
*/	
	wchar_t* text_str = NULL;
	text source_text = {.text_array = NULL, .number_of_strings = 0};
	read_file(&text_str, &source_text, source_file_name);
	wprintf(L"\n2:\n%ls", text_str);
	print_text_array(0, &source_text);//temp
/*
	print_text_array(0, &source_text);//temp

	FILE *finished_file = fopen(finished_file_name, "w");

	sort_text_array(&source_text);
	print_in_file(finished_file, &source_text);
	print_text_array(1, &source_text);//temp
	
	reverse_substrings_in_text(&source_text);
	sort_text_array(&source_text);
	reverse_substrings_in_text(&source_text);
	print_in_file(finished_file, &source_text);
	print_text_array(2, &source_text);//temp

	return_original(&source_text);
	print_in_file(finished_file, &source_text);
	print_text_array(0, &source_text);//temp
*/
	return 0;
}