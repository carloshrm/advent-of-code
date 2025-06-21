#include <stdio.h>
#include <string.h>

int is_vowel(char c)
{
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int has_forbidden_sequence(char *s, size_t i)
{
    return (s[i] == 'a' && s[i + 1] == 'b') || (s[i] == 'c' && s[i + 1] == 'd') || (s[i] == 'p' && s[i + 1] == 'q') || (s[i] == 'x' && s[i + 1] == 'y');
}

int check_string_p1(char *current_string)
{
    int vowel_count = 0;
    int has_double_letter = 0;

    size_t len = strlen(current_string);
    for (size_t i = 0; i < len && !(vowel_count < 3 && has_double_letter); i++)
    {
        if (is_vowel(current_string[i]))
            vowel_count++;

        if (i + 1 < len)
        {
            if (current_string[i + 1] == current_string[i])
                has_double_letter = 1;

            if (has_forbidden_sequence(current_string, i))
                return 0;
        }
    }

    return (vowel_count >= 3 && has_double_letter);
}

int check_string_p2(char *current_string)
{
    int has_repeat = 0;
    int has_pair = 0;

    size_t len = strlen(current_string);
    for (size_t i = 0; i < len; i++)
    {
        if (i + 1 < len && !has_pair)
        {
            for (size_t j = i + 2; j < len; j++)
            {
                if (j + 1 < len)
                {
                    if (current_string[i] == current_string[j] && current_string[i + 1] == current_string[j + 1])
                    {
                        has_pair = 1;
                        break;
                    }
                }
            }
        }

        if (i + 2 < len)
        {
            if (current_string[i] == current_string[i + 2])
            {
                has_repeat = 1;
            }
        }
    }

    return (has_repeat && has_pair);
}

int main()
{
    FILE *file = fopen("./inputs/day5.txt", "r");

    char string[20];
    int nice_string_count = 0;
    while (fgets(string, 20, file))
    {
        if (check_string_p2(string))
            nice_string_count++;
    }

    printf("\n nice strings ::> %d", nice_string_count);
    return 0;
}
