# importing cs50 library to take input
import cs50


# main function
def main():
    # gets user input change in float and rounds it to integer cents
    change = get_cents()
    change = round(change * 100)

    # calculates number of quarter coins
    quarters = calculate_quarters(change)
    change -= quarters * 25

    # calculates number of dime coins
    dimes = calculate_dimes(change)
    change -= dimes * 10

    # calculates number of nickel coins
    nickels = calculate_nickels(change)
    change -= nickels * 5

    # calculates number of penny coins
    penny = calculate_pennies(change)
    change -= penny

    # calculating total number of coins
    coins = quarters + dimes + nickels + penny
    print(coins)


# function to get user input for the amount of change
def get_cents():
    cents = -1
    while cents < 0:
        cents = cs50.get_float("Change owed: ")
    return cents


# function to calculate number of quarter coins for the given amount of change
def calculate_quarters(cent):
    quarters = 0
    while cent >= 25:
        cent -= 25
        quarters += 1
    return quarters


# function to calculate number of dime coins for the given amount of change
def calculate_dimes(cent):
    dimes = 0
    while cent >= 10:
        cent -= 10
        dimes += 1
    return dimes


# function to calculate number of nickel coins for the given amount of change
def calculate_nickels(cent):
    nickels = 0
    while cent >= 5:
        cent -= 5
        nickels += 1
    return nickels


# function to calculate number of penny coins for the given amount of change
def calculate_pennies(cent):
    penny = 0
    while cent >= 1:
        cent -= 1
        penny += 1
    return penny


main()
