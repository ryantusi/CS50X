#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char in, int k);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        if (only_digits(argv[1]))
        {
            int key = atoi(argv[1]);
            string text = get_string("plaintext: ");
            printf("ciphertext: ");
            for (int i = 0; i < strlen(text); i++)
            {
                printf("%c", rotate(text[i], key));
            }
            printf("\n");
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

bool only_digits(string s)
{
    int k = atoi(s);
    if (k <= 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

char rotate(char in, int k)
{
    int pos = (int) in;
    if (k <= 13 && isalpha(in))
    {
        pos += k;
    }
    else if (k > 13 && k < 26 && isalpha(in))
    {
        pos -= k;
    }
    char c = (char) pos;
    return c;
}