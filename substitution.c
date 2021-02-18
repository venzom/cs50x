#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    int len = strlen(argv[1]);
    char upp = 'A', low = 'a';
    // Check to make sure user provides command-line argument(CLA)
    if (argc != 2 || argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (len != 26)
    {
        printf("Key must containg 26 characters.\n");
        return 1;
    } 
    string key = argv[1];
    
    for (int i = 0; i < len; i++)
    {
        if (!(key[i] >= 'a' && key[i] <= 'z' ) && !(key[i] >= 'A' && key[i] <= 'Z'))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1; 
        }

    }

    // Check if the CLA is an integer
    //int key = atoi(argv[1]); // Convert string to real integer
    /*if (key < 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }*/

    // Get plaintext input from user and convert it to cipher using key.
   /* string plain = get_string("plaintext:  ");
    int n = strlen(plain);
    int cipher;
    printf("ciphertext: ");
    for (int i = 0; i < n; i++)
    {
        if (plain[i] >= 'a' && plain[i] <= 'z')
        {
            cipher = (((((int)plain[i] - 97) + 26) + key) % 26) + 97;
            printf("%c", (char)cipher);
        }
        else if (plain[i] >= 'A' && plain[i] <= 'Z')
        {
            cipher = (((((int)plain[i] - 65) + 26) + key) % 26) + 65;
            printf("%c", (char)cipher);
        }
        // Print as is if it is not a letter.
        else
        {
            cipher = (int)plain[i];
            printf("%c", (char)cipher);
        }

    }*/
    printf("\n");

    return 0;
}