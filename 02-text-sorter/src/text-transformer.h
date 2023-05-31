#ifndef TEXT_TRANSFORMER_H
#define TEXT_TRANSFORMER_H
#include "read-file.h"
#include <wchar.h>

void sort_text_array(text *text);
int compare_substring(const void *a, const void *b);
void reverse_substrings_in_text(text *text);
void reverse_substring(substring *substring);
void retutn_original(text *text);
int return_compare_substring(const void *a, const void *b);

#endif