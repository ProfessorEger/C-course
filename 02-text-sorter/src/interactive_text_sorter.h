#ifndef INTERACTIVE_TEXT_SORTING_H
#define INTERACTIVE_TEXT_SORTING_H

#include "read-file.h"
#include "free-string-list.h"
#include <stdio.h>


// TODO: write docs? :|

bool handle_input_argument (int argc, char *argv[], string_buffer *error_buffer);
void print_in_file(FILE *file, text *text);

#endif
