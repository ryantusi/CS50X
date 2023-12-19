# importing packages
import csv
import sys


# main function
def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py database_file sequence_file")
        sys.exit(1)

    # Read database file into a variable
    with open(sys.argv[1]) as database:
        # storing each person's DNA as dictionary into a list
        data_list = []
        data = csv.DictReader(database)
        for row in data:
            data_list.append(row)

        # making a list of subsequence STR
        subsequence = list(data_list[0].keys())
        subsequence.pop(0)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as sequence:
        string = sequence.read()

    # Find longest match of each STR in DNA sequence
    longest_STR = {}
    for seq in subsequence:
        longest_STR[seq] = longest_match(string, seq)

    # Check database for matching profiles
    STR_list = []

    # storing every person's STR list as a dictionary into a list
    for data in data_list:
        data_dict = {}
        for seq in subsequence:
            data_dict[seq] = int(data[seq])
        STR_list.append(data_dict)

    # checking if the longest STR dictionary is in the list of every person's STR dictionary
    if longest_STR in STR_list:
        index = STR_list.index(longest_STR)
        name = data_list[index]["name"]
        print(name)
    else:
        print("No Match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
