// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
} avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);
void swap(avg_temp arr[], int i, int j);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort_cities(void)
{
    // Add your code here
    int max;
    for (int i = 0; i < NUM_CITIES; i++)
    {
        int idx_i = i;
        int idx_j;
        max = temps[i].temp;
        for (int j = i + 1; j < NUM_CITIES; j++)
        {
            if (temps[j].temp > max)
            {
                max = temps[j].temp;
                idx_j = j;
            }
        }
        if (max != temps[i].temp)
        {
            swap(temps, idx_i, idx_j);
        }
    }
}

void swap(avg_temp arr[], int i, int j)
{
    // name swap
    string dupe_city = arr[i].city;
    arr[i].city = arr[j].city;
    arr[j].city = dupe_city;

    // number swap
    int dupe_num = arr[i].temp;
    arr[i].temp = arr[j].temp;
    arr[j].temp = dupe_num;
}