#include "free-string-list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
    string_buffer *error_buffer = initialize_string_buffer();
	int max_input_size = STRING_BUFFER_STRING_SIZE + 20;
    char input[max_input_size];
    char command[15];
    char new_string[STRING_BUFFER_STRING_SIZE];
    int code;

    while (1)
    {
        printf("Enter command: ");
        fgets(input, max_input_size, stdin);
        input[strcspn(input, "\n")] = '\0';

        if (sscanf(input, "%s %99s %d", command, new_string, &code) == 3)
        {
            if (strcmp(command, "a") == 0)
                add_string(error_buffer, new_string, code);
            else if (strcmp(command, "r") == 0)
                remove_string(error_buffer, new_string, code);
            else
                printf("Invalid command: %s\n", command);
        }
        else if (strcmp(input, "p") == 0)
            print_string_buffer(error_buffer);
        else if (strcmp(input, "e") == 0)
            break;
        else
            printf("Invalid input format\n");
    }

    return 0;
}

