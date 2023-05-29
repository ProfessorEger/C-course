#ifndef INTERACTIVE_TEXT_SORTING_H
#define INTERACTIVE_TEXT_SORTING_H

#include "read-file.h"
#include <stdio.h>


bool handle_input_argument (int argc, char *argv[]);
void print_opening_file_result (FILE *file, char *argv[]);
void print_text_array (int messege_code, text *text); //temp

#endif