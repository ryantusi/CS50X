#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //takes input
    string name = get_string("Enter Name: ");
    printf("Hello, %s\n", name);
}