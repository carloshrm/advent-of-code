#include <stdio.h>

int main()
{
    FILE *file = fopen("./inputs/day2.txt", "r");

    char current_line[10];
    int l = 0;
    int w = 0;
    int h = 0;
    int total_paper = 0;
    int total_ribbon = 0;
    while (fscanf(file, "%dx%dx%d", &l, &w, &h) == 3)
    {
        int size_a = l * w;
        int size_b = l * h;
        int size_c = h * w;

        int paper = 2 * (size_a + size_b + size_c);

        if (size_a < size_b)
            paper += size_a < size_c ? size_a : size_c;
        else
            paper += size_b < size_c ? size_b : size_c;

        total_paper += paper;

        int ribbon = (l * w * h);
        if (l < w)
        {
            if (w < h)
                ribbon += (l + w) * 2;
            else
                ribbon += (l + h) * 2;
        }
        else
        {
            if (h < l)
                ribbon += (w + h) * 2;
            else
                ribbon += (w + l) * 2;
        }
        total_ribbon += ribbon;
    }

    printf("\n wrapping paper needed ::> %d", total_paper);
    printf("\n ribbon needed ::> %d", total_ribbon);

    return 0;
}