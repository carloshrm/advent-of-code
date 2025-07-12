#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WIRES 702

char instructions[MAX_WIRES][16];
uint16_t connected_gates[MAX_WIRES] = {0};

int hash_identifier(char *identifier)
{
    if (identifier[0] == '\0')
        return -1;
    else if (identifier[1] == '\0')
        return (identifier[0] - 'a');
    else
        return (((identifier[0] - 'a') * 26) + 26) + (identifier[1] - 'a');
}

int parse_as_signal(char *id)
{
    char *end_ptr = NULL;
    int value = strtol(id, &end_ptr, 10);
    if (id != end_ptr)
        return value;
    else
        return -1;
}

int connect_to(int identifier)
{
    if (connected_gates[identifier] != 0)
        return connected_gates[identifier];

    char *connection = instructions[identifier];

    size_t space_i = 0;
    while (connection[space_i] != '\0' && connection[space_i] != ' ')
        space_i++;

    size_t next_character = space_i + 1;

    size_t len = strlen(connection);
    if (len == space_i)
    {
        // (ID || VAL) -> WIRE
        int value = parse_as_signal(connection);
        if (value != -1)
            return value;
        else
            return connect_to(hash_identifier(connection));
    }
    else if (connection[2] == 'T')
    {
        // NOT ID -> WIRE
        char id[3] = {'\0'};
        strncpy(id, connection + space_i + 1, len - (space_i + 1));
        int signal = connect_to(hash_identifier(id));
        connected_gates[identifier] = ~signal;
        return connected_gates[identifier];
    }
    else
    {
        char id[3] = {'\0'};
        strncpy(id, connection, space_i);
        int signal = parse_as_signal(id);
        int left_signal = signal == -1 ? connect_to(hash_identifier(id)) : signal;

        size_t next_character = space_i + 1;
        if (connection[next_character] == 'L' || connection[next_character] == 'R')
        {
            // ID (LSHIFT | RSHIFT) VAL -> WIRE, assumed no IDs on right of SHIFT
            int right_val = strtol(connection + (next_character + 6), NULL, 10);
            connected_gates[identifier] =
                connection[space_i + 1] == 'L'
                    ? left_signal << right_val
                    : left_signal >> right_val;

            return connected_gates[identifier];
        }
        else if (connection[next_character] == 'A' || connection[next_character] == 'O')
        {
            // (ID | VAL) (AND / NOT) ID -> WIRE, assume no vals on right of & |
            while (connection[next_character++] != ' ')
                ;

            char right_id[3] = {'\0'};
            strncpy(right_id, connection + next_character, len - next_character);
            int right_signal = connect_to(hash_identifier(right_id));

            connected_gates[identifier] =
                connection[space_i + 1] == 'A'
                    ? left_signal & right_signal
                    : left_signal | right_signal;

            return connected_gates[identifier];
        }
    }
}

int main()
{
    FILE *file = fopen("./inputs/day7.txt", "r");

    for (size_t i = 0; i < MAX_WIRES; i++)
        instructions[i][0] = '\0';

    char input[20] = {'\0'};
    while (fgets(input, sizeof(input), file))
    {
        char target_wire[4] = {'\0'};
        char connection[16] = {'\0'};

        sscanf(input, "%[^-]->%s", connection, target_wire);
        int wire_i = hash_identifier(target_wire);
        connection[strlen(connection) - 1] = '\0';

        strcpy(instructions[wire_i], connection);
    }
    fclose(file);

    int a_signal = connect_to(hash_identifier("a"));
    printf("\n signal on a ::> %d", a_signal);

    // part b
    for (size_t i = 0; i < MAX_WIRES; i++)
        connected_gates[i] = 0;

    connected_gates[hash_identifier("b")] = a_signal;

    int a_rewired = connect_to(hash_identifier("a"));
    printf("\n rewired a ::> %d", a_rewired);

    return 0;
}