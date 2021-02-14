#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check to make sure user provides command-line argument(CLA)
    if (argc != 2 || argc == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // Check if the CLA is an integer
    int key = atoi(argv[1]); // Convert string to real integer
    if (key < 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // Get plaintext input from user and convert it to cypher using key
    string plain = get_string("plaintext:  ");
    int n = strlen(plain);
    int cipher;
    printf("ciphertext: ");
    for (int i = 0; i < n; i++)
    {
        cipher = (int)plain[i] + key;
        //cipher[i] = (plain[i] + key) % 26;
        printf("%c", (char)cipher);
    }
    printf("\n");
    
    return 0;
}