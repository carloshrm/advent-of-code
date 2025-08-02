#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_original_characters(char *current_string, size_t len)
{
    int characters = 0;
    for (size_t i = 1; i < len - 1; i++)
    {
        if (current_string[i] == '\\')
        {
            if (current_string[i + 1] == '\\' || current_string[i + 1] == '"')
            {
                i++;
                characters++;
            }
            else if (current_string[i + 1] == 'x')
            {
                if (isxdigit(current_string[i + 2]) && isxdigit(current_string[i + 3]))
                {
                    i += 3;
                    characters++;
                }
                else
                    i += 2;
            }
        }
        else
            characters++;
    }

    return characters;
}

int count_encoded_characters(char *current_string, size_t len)
{
    int extra_encoded = 4;
    for (size_t i = 1; i < len - 1; i++)
    {
        if (current_string[i] == '\\' || current_string[i] == '"')
            extra_encoded++;
    }

    return extra_encoded;
}

int main()
{
    FILE *file = fopen("./inputs/day8.txt", "r");

    char input_ln[100] = {'\0'};
    int total_code = 0;
    int total_char = 0;
    while (fgets(input_ln, sizeof(input_ln), file))
    {
        size_t len = strlen(input_ln) - 1;
        total_code += len;

        // int characters = count_original_characters(input_ln, len);
        int characters = count_encoded_characters(input_ln, len) + len;

        printf("\n string has %d code and %d chars", len, characters);
        total_char += characters;
    }
    fclose(file);

    printf("\n ::> %d code, %d chars for -- %d", total_code, total_char, total_char - total_code);
    return 0;
}