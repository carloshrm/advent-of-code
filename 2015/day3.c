#include <limits.h>
#include <stdio.h>
#include <string.h>

int count_file_lines(FILE *file)
{
    char buffer[50000];
    size_t line_count = 0;

    while (1)
    {
        size_t read_result = fread(buffer, 1, 50000, file);
        if (ferror(file))
            return -1;

        for (size_t i = 0; i < read_result; i++)
        {
            if (buffer[i] == '\n')
                line_count++;
        }

        if (feof(file))
            break;
    }

    return line_count;
}

int main()
{
    FILE *file = fopen("./inputs/day2.txt", "r");

    char current_line[10];

    return 0;
}