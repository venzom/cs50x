#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Determine and print the winner
    if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
    
    // printf("1: %i 2: %i\n", score1, score2);
}

int compute_score(string word) // Compute and return score for string
{
    // Create array of letters
    int array[25];
    int A = 65;
    int sum = 0;
    // Make all words CAPS for ease of manipulations, ignore all characters, and add the score for each letter
    int upper; 
    for (int j = 0; j < 26; j++)
    {
        array[j] = A;
        A++;
        for (int i = 0, n = strlen(word); i < n; i++)
        {
        
            if ((word[i] >= 'a' && word[i] <= 'z') && ((word[i] - 32) == array[j]))
            {
                    sum = sum + POINTS[j];
            }
            else if ((word[i] >= 'A' && word[i] <= 'Z') && (word[i] == array[j]))
            {
                    sum = sum + POINTS[j];
            }
        }
    }
    return sum; 
}
