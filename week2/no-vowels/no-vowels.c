// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    //prompting user to put an argument
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
    else
    {
        //doing all the operations
        string str = argv[1];
        int len = strlen(str);
        char arr[len];
        for (int i = 0; i < len; i++)
        {
            //switch case
            switch (str[i])
            {
                case 'a':
                    arr[i] = '6';
                    break;
                case 'e':
                    arr[i] = '3';
                    break;
                case 'i':
                    arr[i] = '1';
                    break;
                case 'o':
                    arr[i] = '0';
                    break;
                default:
                    arr[i] = str[i];
                    break;
            }
        }
        //printing 
        for (int i = 0; i < len; i++)
        {
            printf("%c", arr[i]);
        }
        printf("\n");
    }
}
