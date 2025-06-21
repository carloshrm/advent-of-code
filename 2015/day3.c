#include <stdio.h>
#include <string.h>

struct Vector2
{
    int x;
    int y;
};

int main()
{
    FILE *file = fopen("./inputs/day3.txt", "r");
    char instructions[10000];
    fgets(instructions, sizeof(instructions), file);
    size_t max_length = strlen(instructions);

    struct Vector2 santa_position = {0, 0};
    struct Vector2 robot_position = {0, 0};

    struct Vector2 visited_houses[max_length];
    size_t houses_i = 0;

    visited_houses[houses_i++] = santa_position;
    int turn_control = 1;

    for (size_t i = 0; i < max_length; i++)
    {
        struct Vector2 current_actor = turn_control ? santa_position : robot_position;
        switch (instructions[i])
        {
        case '>':
            current_actor.x += 1;
            break;
        case '<':
            current_actor.x -= 1;
            break;
        case '^':
            current_actor.y -= 1;
            break;
        case 'v':
            current_actor.y += 1;
            break;
        }

        int already_visited = 0;
        for (size_t j = 0; j <= houses_i; j++)
        {
            if (visited_houses[j].x == current_actor.x && visited_houses[j].y == current_actor.y)
            {
                already_visited = 1;
                break;
            }
        }

        if (already_visited == 0)
            visited_houses[houses_i++] = current_actor;

        if (turn_control)
            santa_position = current_actor;
        else
            robot_position = current_actor;

        turn_control = !turn_control;
    }

    printf("visited houses ::> %d", houses_i);

    return 0;
}