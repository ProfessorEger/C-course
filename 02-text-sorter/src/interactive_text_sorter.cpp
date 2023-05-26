#include "interactive_text_sorter.h"
#include <wchar.h>

void print_opening_file_result (FILE *file)
{
	if(file != NULL)
		wprintf(L"file open\n");
	else
		wprintf(L"unable to open file\n");
}