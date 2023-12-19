// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choosing number of buckets in hash table and declaring variables for hash index and word count
const unsigned int N = 26;
unsigned int hash_index;
unsigned int count;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // getting hash_index using hash function
    hash_index = hash(word);

    // creating a cursor to iterate over the linked list to search for the word in the respective hash_index
    node *cursor = table[hash_index];

    // traversing through the linked list
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
            break;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // returning index of the table to store the word in the respective bucket
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // reading the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Cannot open %s\n", dictionary);
        return false;
    }

    // variable to store each word from the dictionary
    char word[LENGTH + 1];

    // creating linked lists inside the hash table to store all the words from the dictionary
    while (fscanf(file, "%s", word) != EOF)
    {
        // allocating memory for each node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Unable to allocate memory\n");
            return false;
        }

        // copying each word to hash table with hash function which returns the appropriate hash_index for the word
        strcpy(n->word, word);
        hash_index = hash(word);
        n->next = table[hash_index];
        table[hash_index] = n;
        count++; // word count
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // return word count as size
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // creating a flag to return true or false depending on the success of freeing memory
    bool flag = false;

    // create cursor and tmp node to traverse the linked list while cursor saves and moves location, tmp frees the memory allocated
    node *cursor = NULL;
    node *tmp = NULL;

    // traversing through each linked list inside the buckets of the table
    for (int i = 0; i < N; i++)
    {
        // each bucket
        cursor = table[i];

        // freeing each node in the linked list of the respective bucket
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        // checking if freed all memory
        if (cursor == NULL)
        {
            flag = true;
        }
        else
        {
            flag = false;
        }
    }
    return flag;
}
