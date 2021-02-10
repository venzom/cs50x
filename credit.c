#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include <stlib.h>

int main(void)
{
    // Get change owed by user
    long n;
    do
    {
    n = get_long("Number: ");
    }
    while (n < 999999999999 || n > 10000000000000000);
    
    if (n > 4000000000000 && n <= 4999999999999)
    {
        printf("VISA\n");
    }
    else if (n > 3400000000000 && n < 380000000000000)
    {
        printf("AMEX\n");
    }
    else if (n > 40000000000000 && n <= 4999999999999999)
    {
        printf("VISA\n");
    }
    else if (n > 51000000000000 && n < 5600000000000000)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
    
}


  
