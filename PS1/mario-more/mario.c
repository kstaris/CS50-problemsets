#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = 0;
    //Get the number of steps
    while (n < 1 || n > 8)
    {
        n = get_int("Input number of steps from 1 to 8: ");
    }
    int i = 1;
    int y = n;
    for (i = 1; i <= n; i++)
    {
        //Write spaces
        for (y = (n - i); y > 0; y--)
        {
            printf(" ");
        }
        //Write upwards steps
        for (y = 1; y <= i; y++)
        {
            printf("#");
        }

        printf("  ");
        //Write downwards steps
        for (y = 1; y <= i; y++)
        {
            printf("#");
        }
        printf("\n");
    }

}