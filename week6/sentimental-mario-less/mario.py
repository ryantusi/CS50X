# main function
def main():
    # gets height from user
    height = get_height()
    count = 1
    n = height

    # prints pyramid
    while n > 0:
        print(" " * (height - count), end="")
        print("#" * count)
        count += 1
        n -= 1


def get_height():
    # prompts user for valid input
    while True:
        try:
            n = int(input("Height: "))
            if n > 0 and n < 9:
                return n
        except ValueError:
            print("Enter integer between 1-8")


# calling main function
main()
