#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = 0;
    while (n<1 || n>8)
    {
        n = get_int("Input number of steps from 1 to 8: ");
    }
    int i = 1;
    int y = n;
    for (i=1; i<=n; i++)
    {
        for (y = (n-i); y>0; y--)
        {
            printf(" ");
        }
        for (y = 1; y<=i; y++)
        {
            printf("#");
        }
        printf("\n");
    }

}