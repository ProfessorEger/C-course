#ifndef TEXT_TRANSFORMER_H
#define TEXT_TRANSFORMER_H
#include "read-file.h"
#include <wchar.h>


// TODO: write docs, docs are good, docs are life, dogs thank you for docs :(

void sort_text_array(text *text);
int compare_substring(const void *a, const void *b);
void reverse_substrings_in_text(text *text);
void reverse_substring(substring *substring);
void return_original(text *text);

#endif
