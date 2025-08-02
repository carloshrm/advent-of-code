#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 11
// hash function from k&r 2
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

unsigned search(int matrix[HASHSIZE][HASHSIZE], size_t current_node, bool visited[HASHSIZE])
{
    if (visited[current_node]) {
        return 0;
    }
    visited[current_node] = true;
    printf("\n >> at node %i", current_node);

    int shortest_path = __INT_MAX__;
    size_t path_i = -1;
    for (size_t i = 0; i < HASHSIZE; i++)
    {
        if (i == current_node)
            continue;

        if (matrix[current_node][i] != __INT_MAX__)
        {
            int current_search = search(matrix, i, visited);
            printf(" == searched to %i | cost %i |", i, current_search);
            if (current_search != 0 && current_search < shortest_path)
            {
                shortest_path = current_search;
                path_i = i;
            }
        }
    }
    printf(" :: shortest path on node %i is to node %i", current_node, path_i);
    if (path_i != -1)
        return shortest_path + matrix[current_node][path_i];
    else
        return 0;
}

int main()
{
    FILE *file = fopen("./inputs/day9.txt", "r");
    int adjacency_matrix[HASHSIZE][HASHSIZE];
    for (size_t i = 0; i < HASHSIZE; i++)
        for (size_t j = 0; j < HASHSIZE; j++)
            adjacency_matrix[i][j] = __INT_MAX__;

    bool valid_nodes[HASHSIZE] = {false};

    char input_ln[100] = {'\0'};
    int cost = 0;
    char orig[20] = {'\0'};
    char dest[20] = {'\0'};
    while (fgets(input_ln, sizeof(input_ln), file))
    {
        sscanf(input_ln, "%s to %s = %i", orig, dest, &cost);
        int origin_hash = hash(orig);
        valid_nodes[origin_hash] = true;

        int destin_hash = hash(dest);
        valid_nodes[destin_hash] = true;

        adjacency_matrix[origin_hash][destin_hash] = cost;
    }
    fclose(file);

    int shortest_path = 0;
    for (size_t i = 0; i < HASHSIZE; i++)
    {
        if (valid_nodes[i])
        {
            valid_nodes[i] = false;

            bool visited_nodes[HASHSIZE] = {false};
            int current_path = search(adjacency_matrix, i, visited_nodes);
            if (current_path < shortest_path)
                shortest_path = current_path;
        }
    }
    printf("\n !! >> shortest path %i", shortest_path);

    return 0;
}