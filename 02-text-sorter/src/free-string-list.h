 const int NULL_CODE = -1024;

#ifndef FREE_LIST_H
#define FREE_LIST_H

typedef struct error
{
	string_info *next;	 // Указатель на следующую строку
	string_info *prev;	 // Указатель на предыдущую  строку
	//bool string_is_busy; // Занятая ли строка
    //    ^^^^^^ TODO: I'd rather make this just an internal
    //                 string buffer char string[SIZE];


    // [.      .                      ]
    // [^   ] [^   ] [string_info   |message|]
    // TODO:  ^^^^^^ you do this
    // TODO:         ^^^^^^^^^^^^^^^^^^^^^^^^^
    //               but it's better to do this

    // NOTE: this is how stack works:

    // Imagine we have such code:

    // foo() // void foo() { bar(); }
    // bar() // void bar() { xyz(); }

    // Stack will look like this:

    // [ foo         ] // foo called
    // [ foo bar     ] // bar called from foo
    // [ foo bar xyz ] // and so on...
    // [ foo bar     ] // xyz finished (local variable of xyz deallocated)
    // [ foo         ] // and so on...
    // [ ...         ]


    // NOTE: This is how array is JS look like:

    //       [ ...... el 1 data ]
    //       ^
    //       |
    // [ el0 el1 el2 el3 ]  and so on
    //   |
    //   v
    //   [ ...... el 0 data ]

    // But in C++ we can do a lot better, like so:

    // [ [ ...... el 0 data ] [ ...... el 1 data ] el2 el3 ]  and so on

    // We removed indirection, it's now all just one flat piece.
    // And it's a lot easier on allocation system this way and also
    // a lot faster to access (due to reduced indirection and
    // cache-friendliness).

	int code;			 // код ошибки
	char string[];		 // Указатель на эту строку в string_buffer
} error;

typedef struct error_buffer // Хранит буффер для хранения строк и информацию о нем
{
	int number_of_strings;
	int string_size;
	error *first_used_string;	 // Указатель на информацию о первой строке
	error *first_free_string;
	error error[];			 // Массив информаци о каждой строке

    // TODO: can you make this a cyclic buffer?

    // This is your regular doubly-linked list:
    // NULL <- [  ] [  ] [  ] [  ] [  ] [  ] [  ] [  ] -> NULL

    // Cyclic buffer looks like this:
    //      ┌─────────────────────────────────────┐
    //      │                                     │
    //      │                                     ↓
    //      └─ [xx] [  ] [  ] [  ] [  ] [  ] [  ] [  ] ─┐
    //         ↑                                        │
    //         │                                        │
    //         └────────────────────────────────────────┘

    // Imagine [xx] is a special element not visible for user.

    //                   ┌─┬─┐
    // Use this to draw: │ │ │ ~~~~~~~~~~~~~~~~~~~~~ 0_0
    //                   └─┴─┘

} error_buffer;


// TODO: try to write DOCS in doxygen format :) 

void initialize_string_buffer(error_buffer *sb, int number_of_strings, int string_size);
void add_string(error_buffer *sb, const char *new_string, int code);			 // Добавляет строку в error_buffer
void remove_string(error_buffer *sb, const char *unnecessary_string, int code); // Удаляет строку из error_buffer
void print_string_buffer(error_buffer *sb);
int return_string_code(error_buffer *sb);
int find_string_buffer_size(int number_of_strings, int string_size);

#endif
