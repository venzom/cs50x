#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    // Check to make sure user provides at least 1, but no more than, command-line argument(CLA)
    if (argc == 1 || argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check to make sure "key" CLA is exactly 26 characters
    int len = strlen(argv[1]);
    if (len != 26)
    {
        printf("Key must containg 26 characters.\n");
        return 1;
    }


    // Make sure "key" CLA only contains alphabetic characters and doesn't contain repeated characters
    string key = argv[1];
    char upp = 'A', low = 'a';
    char uppAr[26], lowAr[26];
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        // Check for alpabetic characters by checking for any characters outside the alphabet
        if (!(key[i] >= 'a' && key[i] <= 'z') && !(key[i] >= 'A' && key[i] <= 'Z'))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        // Check for repeated characters by couting each occurence of a character that should always be equal to i
        else if (i != count)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
        for (int j = 0; j < len; j++)
        {
            if (key[j] == upp || key [j] == low)
            {
                count++;
            }
        }
        uppAr[i] = upp;
        lowAr[i] = low;
        upp++, low++;
    }


    // Get plaintext input from user and convert it to cipher using key.
    string plain = get_string("plaintext:  ");
    int n = strlen(plain);
    char cipher[n];
    printf("ciphertext: ");
    for (int k = 0; k < n; k++)
    {
        if (plain[k] >= 'a' && plain[k] <= 'z')             // Convert plain lowercase letters only to lowercase cipher
        {
            for (int l = 0; l < len; l++)
            {
                if (plain[k] == lowAr[l])
                {
                    printf("%c", tolower(key[l]));
                }
            }

        }
        else if (plain[k] >= 'A' && plain[k] <= 'Z')        // Convert plain uppercase letter to uppercase cypher
        {
            for (int l = 0; l < len; l++)
            {
                if (plain[k] == uppAr[l])
                {
                    printf("%c", toupper(key[l]));
                }
            }
        }
        else
        {
            printf("%c", plain[k]);
        }
    }
    printf("\n");
    return 0;
}