// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <cs50.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

int nWords = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *tmp = table[index];
    while (tmp != NULL)
    {
        if (strcasecmp(tmp -> word, word) == 0)
        {
            return true;
        }
        tmp = tmp -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open dictionary");
        return false;
    }
    //Read string
    char str[LENGTH + 1];
    while (fscanf(dict, "%s", str) != EOF)
    {
        node *nNode = malloc(sizeof(node));
        if (nNode == NULL)
        {
            printf("Run out of memmory");
            return false;
        }
        strcpy(nNode -> word, str);
        int index = hash(nNode -> word);
        nNode -> next = table[index];
        table[index] = nNode;
        nNode = NULL;
        nWords++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (nWords > 0)
    {
        return nWords;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor;
        cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = tmp -> next;
            free(tmp);
        }
    }
    return true;
}
