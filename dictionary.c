// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000000;

// integer for hash values
unsigned int value;

// Variable for counting words
unsigned int count;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash word to get value
    value = hash(word);
    
    node *check = table[value];
    
    while (check != NULL)
    {
        if (strcasecmp(word, check->word) == 0)
        {
            return true;
        }
        
        check = check->next;
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash function from http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 0;
    int c;
    
    while ((c = tolower(*word++)))
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // 
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    
    // Variable to store word
    char word[LENGTH + 1];
    
    while (fscanf(file, "%s", word) != EOF)
    {
        // allocate memory for each node
        node *n = malloc(sizeof(node));
        
        //check for null
        if (n == NULL)
        {
            return false;
        }
        
        // pointer to next node and word
        strcpy(n->word, word);
        // Get value for word from hash
        value = hash(word);
        // set new pointer
        n->next = table[value];
        // set head to new pointer
        table[value] = n;
        // Count words
        count++;
    }
    
    fclose(file);
    
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (count > 0)
    {
        return count;
    }
    
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *check = table[i];
        
        while (check)
        {
            node *tmp = check;
            
            check = check->next;
            
            free(tmp);
        }
        
        if (i == N - 1 && check == NULL)
        {
            return true;
        }
        
    }
    return false;
}
