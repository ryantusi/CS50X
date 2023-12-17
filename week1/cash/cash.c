#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // gets cents
    int cent;
    do
    {
        cent = get_int("Change owed: ");
    }
    while (cent < 0);
    return cent;
}

int calculate_quarters(int cents)
{
    // gets quarters
    int quarter = 0;
    while (cents >= 25)
    {
        cents -= 25;
        quarter++;
    }
    return quarter;
}

int calculate_dimes(int cents)
{
    // gets dimes
    int dime = 0;
    while (cents >= 10)
    {
        cents -= 10;
        dime++;
    }
    return dime;
}

int calculate_nickels(int cents)
{
    // gets nickels
    int nickel = 0;
    while (cents >= 5)
    {
        cents -= 5;
        nickel++;
    }
    return nickel;
}

int calculate_pennies(int cents)
{
    // gets pennies
    int penny = 0;
    while (cents >= 1)
    {
        cents -= 1;
        penny++;
    }
    return penny;
}
