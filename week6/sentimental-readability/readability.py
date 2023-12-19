# import packages
import cs50
import string


# main function
def main():
    # prompting user for input
    sentence = cs50.get_string("Input: ")

    # computing L and S, then index using specific formula
    L = count_letters(sentence) / count_words(sentence) * 100
    S = count_sentences(sentence) / count_words(sentence) * 100
    index = 0.0588 * L - 0.296 * S - 15.8

    # rounding index to nearest int to get grade
    grade = round(index)

    # printing grade based on value
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


# function to count letters
def count_letters(s):
    letters = 0
    for i in s:
        if i.isalnum():  # checking if letter alpha-numberic
            if i not in string.punctuation:  # checking if its not a punctuation
                letters += 1
    return letters


# function to count words
def count_words(s):
    words = 1
    for i in range(len(s)):
        # checking if its a space and next is not space
        if s[i].isspace() and (s[i + 1].isspace() != True):
            words += 1
    return words


# function to count sentences
def count_sentences(s):
    sentences = 0
    for i in s:
        if i == "." or i == "!" or i == "?":
            sentences += 1
    return sentences


main()
