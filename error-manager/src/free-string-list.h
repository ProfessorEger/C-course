#define NULL_CODE -1024

#ifndef FREE_LIST_H
#define FREE_LIST_H

typedef struct string_info
{
	string_info *next;	 // Указатель на следующую строку
	string_info *prev;	 // Указатель на предыдущую  строку
	bool string_is_busy; // Занятая ли строка
	char *string;		 // Указатель на эту строку в string_buffer
	int code;			 // код ошибки
} string_info;

typedef struct string_buffer // Хранит буффер для хранения строк и информацию о нем
{
	int number_of_strings;
	int string_size;
	char *buffer;
	string_info *info;			 // Массив информаци о каждой строке
	string_info *first_string;	 // Указатель на информацию о первой строке
	string_info *closing_string; // Указатель на информацию о последней строке
} string_buffer;

string_buffer initialize_string_buffer(int number_of_strings, int string_size);
void add_string(string_buffer *sb, char *new_string, int code);			   // Добавляет строку в string_buffer
void remove_string(string_buffer *sb, char *unnecessary_string, int code); // Удаляет строку из string_buffer
void print_string_buffer(string_buffer *sb);
int return_string_code(string_buffer *sb);

#endif