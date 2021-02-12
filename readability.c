#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string s);    // Count the letters in the inputed text from user.
int count_spaces(string s);     // Count the words by counting the spaces in the text + 1
int count_p(string s);          // Count the sentences by counting the punctuations (? ! .)

int main(void)
{
    // Get input from user
    string s = get_string("Text: ");

    // Calculate words and sentences
    int letters = count_letters(s);
    int words = count_spaces(s);
    int sentences = count_p(s);
    float L = letters * 100.00 / words;
    float S = sentences * 100.00 / words;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.f\n", round(index));
    }
}


// Count just the letters in the text
int count_letters(string s)
{
    int letters = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            letters++;
        }
    }
    return letters;
}


// Count spaces + 1 to count the number of words in the sentence
int count_spaces(string s)
{
    int words = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == 32)
        {
            words++;
        }
    }
    return words + 1;
}

// Count punctuation(! ? .) to get the number of sentences.
int count_p(string s)
{
    int sent = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == 33 || s[i] == 46 || s[i] == 63)
        {
            sent++;
        }
    }
    return sent;
}