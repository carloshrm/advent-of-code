#include <limits.h>
#include <stdio.h>

int main()
{
    FILE *file = fopen("./inputs/day1.txt", "r");
    char input[8000];
    fgets(input, 8000, file);
    fclose(file);

    int floor = 0;
    int basement_pos = INT_MAX;

    size_t i = 0;
    char current_instr = input[i];
    while (current_instr != '\0')
    {
        floor += current_instr == '(' ? 1 : -1;
        if (floor < 0 && i < basement_pos)
        {
            basement_pos = i;
        }

        current_instr = input[++i];
    }

    printf("\n floor ::> %d", floor);
    printf("\n basement ::> %d", basement_pos + 1);
    return 0;
}