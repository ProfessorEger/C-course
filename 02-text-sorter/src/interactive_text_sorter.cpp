#include "interactive_text_sorter.h"
#include <wchar.h>

void print_opening_file_result(FILE *file, char *argv[])
{
	if (file != NULL)
		wprintf(L"textsorter: file '%s' is open\n", argv[1]);
	else
		wprintf(L"textsorter: cannot stat '%s': No such file\n", argv[1]);
}

bool handle_input_argument(int argc, char *argv[])
{
	if(argc > 2)
		return true;
	else if(argc == 2)
		wprintf(L"textsorter: missing destination file operand after '%s'\n", argv[1]);
	else
		wprintf(L"textsorter: missing file operand\n");

	return false;
}

void print_text_array (int messege_code, text *text) //temp
{
	switch (messege_code)
	{
	case 0:
		wprintf(L"original_text:\n\n");
		break;
	default:
		wprintf(L"\nsort №%-2d\n\n", messege_code);
		break;
	}

	for (int i=0;i < (*text).number_of_strings; i++) // temp (вывод файла в консоль)
	{
		wprintf(L"№%-7d %ls\n", (*text).text_array[i].string_number, (*text).text_array[i].dynamic_string);
	}
}