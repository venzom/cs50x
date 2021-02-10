#include <cs50.h>
#include <stdio.h>
#include <string.h>
//#include <stlib.h>

int main(void)
{
    // Get input from user between 1 - 8
    int n = 0;
    do
    {
    n = get_int("Height: ");
    }
    while (n >= 9 || n <= 0);
    
    // Assign n to m for 'for' loop so it doesn' affect n
    int m = n;
    char space[128] = " ";
    char sp = ' ';
    
    for (int j = 1; j < n; j++)
    {
        strncat(space, &sp, 1);
    }
    
    for (int i = 0; i < n; i++)
    {
        m--;
        space[m] = '#';
        printf("%s\n", space);
    }
}
