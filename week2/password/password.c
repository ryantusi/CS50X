// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int len = strlen(password);
    int lower = 0, upper = 0, num = 0, sym = 0;
    for (int i = 0; i < len; i++)
    {
        if (isupper(password[i]))
        {
            upper++;
        }
        else if (islower(password[i]))
        {
            lower++;
        }
        else if (isdigit(password[i]))
        {
            num++;
        }
        else if (!isalpha(password[i]) && !isdigit(password[i]))
        {
            sym++;
        }
    }
    if (lower > 0 && upper > 0 && num > 0 && sym > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
