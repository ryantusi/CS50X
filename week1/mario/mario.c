#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //getting height
    int size;
    do
    {
        size = get_int("Enter Height: ");
    }
    while (size < 1 || size > 8);

    //pyramid building
    for (int i = size; i >= 1; i--)
    {
        //inner loop with conditions
        for (int j = 1; j <= size; j++)
        {
            if (i <= j)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}