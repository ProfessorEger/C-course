#include "test-macros.h"
#include "../text-transformer.h"
#include "../read-file.h"
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

int cmpr_string(wchar_t *str1, wchar_t *str2)
{
	return wcscmp(str1, str2);
}

int main(void)
{
	setlocale(LC_ALL, "en_US.UTF-8");
	text source_text = {.text_array = NULL, .number_of_strings = 0};
	wchar_t *text_str  = L"букварь\0варенье\0арбуз\0анаконда";

    // TODO: write tests :)
    // TODO: clang++ -E ... will output your file with every macro expanded
	TEST_FUNC_PTR(1, read_file, cmpr_string, &text_str, L"букварь\0варенье\0арбуз\0анаконда", &text_str, &source_text, "text.txt");

	free(source_text.text_array);
	free(text_str);
}

