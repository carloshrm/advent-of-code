#include <limits.h>
#include <openssl/md5.h>
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *file = fopen("./inputs/day4.txt", "r");
    char key[10];
    fgets(key, sizeof(key), file);
    key[strcspn(key, "\n")] = 0;

    for (size_t i = 0; i < INT_MAX; i++)
    {
        unsigned char result[MD5_DIGEST_LENGTH];

        char input[32];
        sprintf(input, "%s%d", key, i);

        MD5(input, strlen(input), result);

        if (result[0] == 0x00 && result[1] == 0x00 && result[2] == 0x00)
        {
            for (size_t j = 0; j < MD5_DIGEST_LENGTH; j++)
                printf("%02x ", result[j]);

            printf("\n number ::> %d", i);
            break;
        }
    }

    return 0;
}