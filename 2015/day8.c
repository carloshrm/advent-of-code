#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

        int characters = 0;
        for (size_t i = 0; i < len; i++)
        {
            if (input_ln[i] == '"')
                continue;

            if (input_ln[i] == '\\')
            {
                if (input_ln[i + 1] == '\\' || input_ln[i + 1] == '"')
                {
                    i++;
                    characters++;
                }
                else if (input_ln[i + 1] == 'x')
                {
                    if (isxdigit(input_ln[i + 2]) && isxdigit(input_ln[i + 3]))
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
        // printf("\n string has %d code and %d chars", len, characters);
        total_char += characters;
    }
    fclose(file);

    printf(" ::> %d code, %d chars for -- %d", total_code, total_char, total_code - total_char);
    return 0;
}