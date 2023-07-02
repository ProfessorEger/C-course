#define NULL_CODE -1024 // TODO: Why you define this before include guard?
                        // TODO: Just use const's instead of macros!

#ifndef FREE_LIST_H
#define FREE_LIST_H

typedef struct string_info
{
	string_info *next;	 // Указатель на следующую строку
	string_info *prev;	 // Указатель на предыдущую  строку
	bool string_is_busy; // Занятая ли строка
	char *string;		 // Указатель на эту строку в string_buffer
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
} string_info;


// TODO: name, why is it a string_buffer?
// struct_string_buffer_that_contains_number_of_strings_and_string_size_and_buffer_and_info_and_first_string_and_closing_string

// A much better name would be, for example error_buffer

typedef struct string_buffer // Хранит буффер для хранения строк и информацию о нем
{
	int number_of_strings;
	int string_size;
	char *buffer;
	string_info *info;			 // Массив информаци о каждой строке
	string_info *first_string;	 // Указатель на информацию о первой строке
	string_info *closing_string; // Указатель на информацию о последней строке

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

} string_buffer;


// TODO: try to write DOCS in doxygen format :) 

string_buffer initialize_string_buffer(int number_of_strings, int string_size);

// TODO: actual type of "string literal" is const char*
void add_string(string_buffer *sb, char *new_string, int code);			 // Добавляет строку в string_buffer
void remove_string(string_buffer *sb, char *unnecessary_string, int code); // Удаляет строку из string_buffer
void print_string_buffer(string_buffer *sb);
int return_string_code(string_buffer *sb);

#endif
