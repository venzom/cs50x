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
    while (n < 0);//(n < 999999999999 || n > 10000000000000000);
    
    // Count number of digits in Array
    int c = 0; 
    long number  = n;
    
    while (number != 0)
    {
        number /= 10;
        c++;
    }
    
    // Add each digit of CC into an array
    long cc[c]; // Credit card array
    c = 0;    
    number = n;
    while (n != 0)
    {
        cc[c] = n % 10;
        n /= 10;
        c++;
    }
    
    // Multiply each digit by 2, starting with the second to last digit, then add the products dicits together with result of 'sum'
    int mul = 0, sum = 0, mulSum = 0;
    for (int i = 1; i <= c - 1; i += 2)
    {
        mul = cc[i] * 2;
        for (int j = 0; j < 2; j++)
        {
            mulSum = mul % 10;
            mul /= 10;
            sum = sum + mulSum;
        }
    }
    
    // Add to the sum to the sum of the digits that weren't multiplied by 2 
    for (int k = 0; k <= c - 1; k += 2)
    {
        mul = cc[k];
        sum = sum + mul;
    }
    
    // Checksum to verify the last digit is zero
    int checkSum = sum % 10; 
    
    // Check each for validity of number entered
    if (c < 13 || c > 16 || checkSum != 0)
    {
        printf("INVALID\n");
    }
    // Determine what type of card it is and print result
    else if ((c == 13 || c == 16) && (cc[12] == 4 || cc[15] == 4))
    {
        printf("VISA\n");
    }
    else if (c == 15 && cc[14] == 3 && (cc[13] == 4 || cc[13] == 7))
    {
        printf("AMEX\n");
    }
    else if (c == 16 && cc[15] == 5 && (cc[14] == 1 || cc[14] == 2 || cc[14] == 3 || cc[14] == 4 || cc[14] == 5))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}