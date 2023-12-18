#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//prototypes
int count_letters(string s);
int count_words(string s);
int count_sentances(string s);

int main(void)
{
    //getting a string
    string str = get_string("Text: ");

    //getting letters, words, and sentances with functions
    float L = (count_letters(str) / (float)count_words(str)) * 100;
    float S = (count_sentances(str) / (float)count_words(str)) * 100;

    //computing and rounding
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = (int) round(index);

    //printing appropriate grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int count_letters(string s)
{
    //function to find letters
    int letters = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (isalnum(s[i]) && !ispunct(s[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string s)
{
    //function to find words
    int words = 1;
    for (int i = 0; i < strlen(s); i++)
    {
        if (isspace(s[i]) && !isspace(s[i + 1]))
        {
            words++;
        }
    }
    return words;
}

int count_sentances(string s)
{
    //function to find sentances
    int sentances = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentances++;
        }
    }
    return sentances;
}