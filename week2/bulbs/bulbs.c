#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string msg = get_string("Message: ");
    int len = strlen(msg);

    //Storing ASCII values of chars in array
    int arr[len];
    for (int i = 0; i < len; i++)
    {
        arr[i] = (int) msg[i];
    }
    int temp = 0;   //variable to store one value to convert to binary

    //New array to store binary digits for a single ASCII Value
    int newarr[8];
    for (int j = 0; j < 8; j++)
    {
        newarr[j] = 0;
    }

    //iterating through the ASCII Values
    for (int z = 0; z < len; z++)
    {
        temp = arr[z];              //setting one value at a time
        for (int j = 0; j < 8; j++)
        {
            newarr[j] = 0;          //setting all the binary digits to 0
        }
        //Computing the 1s places
        while (temp > 0)
        {
            if (temp >= 128)
            {
                temp -= 128;
                newarr[0] = 1;
            }
            else if (temp >= 64)
            {
                temp -= 64;
                newarr[1] = 1;
            }
            else if (temp >= 32)
            {
                temp -= 32;
                newarr[2] = 1;
            }
            else if (temp >= 16)
            {
                temp -= 16;
                newarr[3] = 1;
            }
            else if (temp >= 8)
            {
                temp -= 8;
                newarr[4] = 1;
            }
            else if (temp >= 4)
            {
                temp -= 4;
                newarr[5] = 1;
            }
            else if (temp >= 2)
            {
                temp -= 2;
                newarr[6] = 1;
            }
            else if (temp >= 1)
            {
                temp -= 64;
                newarr[7] = 1;
            }
        }
        //printing the binary digits from the newarr by calling the function
        for (int x = 0; x < 8; x++)
        {
            print_bulb(newarr[x]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
