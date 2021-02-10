#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include <stlib.h>

int main(void)
{
    // Get change owed by user
    float n = 0;
    do
    {
    n = get_float("Change Owed: ");
    }
    while (n <= 0);
    //float change = n - (int)n;
    float change = n;
    int cents = round(change *100);
    int coins = 0;
    
    do
    {
        if (cents >= 25)
        {
            cents = cents - 25;
        }
        else if (cents >= 10)
        {
            cents = cents - 10;
        }
        else if (cents >= 5)
        {
            cents = cents - 5;
        }
        else if (cents >= 1)
        {
            cents = cents - 1;
        }
        else
        {
            break;
        }
        //printf("%i\n", cents);
        coins++;
    }
    while (cents > 0);
    printf("%i\n", coins);
}
