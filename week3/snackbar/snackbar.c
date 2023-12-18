// Practice using structs
// Practice writing a linear search function

/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10

// Menu itmes have item name and price
typedef struct
{
    string item;
    float price;
} menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(void);

// Calculate total cost
float get_cost(string item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        if (get_cost(item) == 1)
        {
            printf("Invalid Item!\n");
        }
        else
        {
            total += get_cost(item);
        }
    }

    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first four items to the menu array
void add_items(void)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        switch (i)
        {
            case 0:
                menu[i].item = "Burger";
                menu[i].price = 9.5;
                break;
            case 1:
                menu[i].item = "Vegan Burger";
                menu[i].price = 11;
                break;
            case 2:
                menu[i].item = "Hot Dog";
                menu[i].price = 5;
                break;
            case 3:
                menu[i].item = "Cheese Dog";
                menu[i].price = 7;
                break;
            case 4:
                menu[i].item = "Fries";
                menu[i].price = 5;
                break;
            case 5:
                menu[i].item = "Cheese Fries";
                menu[i].price = 6;
                break;
            case 6:
                menu[i].item = "Juice";
                menu[i].price = 7;
                break;
            case 7:
                menu[i].item = "Cold Brew";
                menu[i].price = 3;
                break;
            case 8:
                menu[i].item = "Water";
                menu[i].price = 2;
                break;
            case 9:
                menu[i].item = "Soda";
                menu[i].price = 2;
                break;
        }
    }
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    float price;
    bool flag = false;
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (strcmp(item, menu[i].item) == 0)
        {
            price = menu[i].price;
            flag = true;
            break;
        }
    }
    if (flag)
    {
        return price;
    }
    else
    {
        return 1;
    }
}