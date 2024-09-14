#ifndef FREE_LIST_H
#define FREE_LIST_H

const int STRING_BUFFER_STRING_SIZE = 100;
const int STRING_BUFFER_NUMBER_OF_STRINGS = 5; 
const int STRING_BUFFER_NULL_CODE = -1024;

typedef struct string_info
{
	string_info *next;	 		// Указатель на следующую строку
	string_info *prev;	 		// Указатель на предыдущую  строку
	bool string_is_busy; 		// Занятая ли строка
	int code;			 		// код ошибки
	char string[STRING_BUFFER_STRING_SIZE + 1];	// строка
} string_info;


typedef struct string_buffer // Хранит буффер для хранения строк и информацию о нем
{
	string_info *current_string;
	string_info *first_string;
	string_info *closing_string; // Указатель на информацию о последней строке
	string_info buffer[STRING_BUFFER_NUMBER_OF_STRINGS];
} string_buffer;


string_buffer *initialize_string_buffer();
void add_string(string_buffer *sb, char *new_string, int code);
void remove_string(string_buffer *sb, char *unnecessary_string, int code); // Удаляет строку из string_buffer
void print_string_buffer(string_buffer *sb);
int return_string_code(string_buffer *sb);

#endif