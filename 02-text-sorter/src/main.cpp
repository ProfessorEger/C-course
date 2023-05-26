#include "read-file.h"
#include "interactive_text_sorter.h"
#include <locale.h>
#include <wchar.h>

int main()
{
	setlocale(LC_ALL, "en_US.UTF-8");

	char source_file_name[] = "../original-text.txt";//temp, имя файла должно передаваться при вызове
	FILE *source_file = open_file(source_file_name);
	print_opening_file_result (source_file);
	if (source_file == NULL) 
		return 0;
	
	text source_text = {.text_array = NULL, .number_of_string = 0};
	read_file(&source_text, source_file);

	for (int i=0;i < source_text.number_of_string; i++) // temp (вывод файла в консоль)
	{
		wprintf(L"№%-7d %ls\n", source_text.text_array[i].string_number, source_text.text_array[i].dynamic_string);
	}
	
	/*
	Тут должно быть другое. Расписанно в файле program-plan.txt и в переписке с Сашей

	sort_by_start();
	sort_by_end();
	print_result_text();
	*/
	return 0;
}