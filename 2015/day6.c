#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_LIGHTS 1000

typedef struct
{
    int x;
    int y;
} Vector2;

int main()
{
    FILE *file = fopen("./inputs/day6.txt", "r");
    int **lights = malloc(sizeof(int *) * N_LIGHTS);
    for (size_t i = 0; i < N_LIGHTS; i++)
        lights[i] = calloc(N_LIGHTS, sizeof(int) * N_LIGHTS);

    char type[4];
    Vector2 start = {0, 0};
    Vector2 end = {0, 0};
    char input[40];
    while (fgets(input, sizeof(input), file))
    {
        int brightness = 2;
        if (input[5] == 'e')
            sscanf(input, "toggle %d,%d through %d,%d", &start.x, &start.y, &end.x, &end.y);
        else
        {
            sscanf(input, "turn %s %d,%d through %d,%d", type, &start.x, &start.y, &end.x, &end.y);
            brightness = type[1] == 'f' ? -1 : 1;
        }

        for (size_t i = start.x; i <= end.x; i++)
        {
            for (size_t j = start.y; j <= end.y; j++)
            {
                lights[i][j] += brightness;
                if (lights[i][j] < 0)
                    lights[i][j] = 0;
            }
        }
    }
    fclose(file);

    int total_brightness = 0;
    for (size_t i = 0; i < N_LIGHTS; i++)
    {
        for (size_t j = 0; j < N_LIGHTS; j++)
            total_brightness += lights[i][j];
    }
    printf("lights on ::> %d", total_brightness);

    return 0;
}

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
    rewind(file);

    return line_count;
}