#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long number = get_long("Insert your credit card number: ");
//Find the number of characters
    long n = number;
    int CharNum = 0;
    for (CharNum = 0; n >= 1; CharNum++)
    {
        n = n / 10;
    }

//Get first 2 numbers
    long twoNumbers;
    int tempCharNum = CharNum;
    long x = pow(10, (CharNum - 2));
    long z =  number % x;
    twoNumbers = (number - z) / x;

//Get first 1 number

    x = pow(10, (CharNum - 1));
    z =  number % x;
    long  oneNumber = (number - z) / x;

//Get multiplied sum of every second number

    int nu = 1;
    long tempNum = number;
    int summa2 = 0;
    for (nu = 1; nu <= CharNum; nu++)
    {
        long power = pow(10, nu);
        long  cipars1 = tempNum % power;
        tempNum = tempNum - cipars1;
        if (nu % 2 != 0)
        {
            summa2 = summa2 + (cipars1 / (power / 10));
        }
    }
//Get sum of every first

    nu = 1;
    tempNum = number;
    int summa1 = 0;
    for (nu = 1; nu <= CharNum; nu++)
    {
        long power = pow(10, nu);
        long  cipars1 = tempNum % power;
        tempNum = tempNum - cipars1;
        if (nu % 2 == 0)
        {
            cipars1 = cipars1 / (power / 10);
            printf("cipars1 = %ld\n",cipars1);
            if (cipars1 > 4)
            {
                cipars1 = cipars1 * 2;
                summa1 = summa1 + (cipars1 % 10);
                long test1 = (cipars1 % 10);
                printf("test1 = %ld\n", test1);
                cipars1 = cipars1 - (cipars1 % 10);
                summa1 = summa1 + (cipars1 % 100) / 10;
                long test2 = (cipars1 % 100) / 10;
                printf("test2 = %ld\n", test2);
            }
            else
            {
                summa1 = summa1 + cipars1 * 2;
            }
        }
    }
    int summa = summa1 + summa2;
    printf("summa1 = %d\n", summa1);
    printf("summa2 = %d\n", summa2);
    printf("summa = %d\n", summa);
    int atlikums = summa % 10;
    printf("CharNum = %d\n", CharNum);
    printf("oneNumber = %ld\n", oneNumber);
    printf("atlikums = %d\n", atlikums);
    if (CharNum == 15 && twoNumbers == 34 && atlikums == 0)
    {
        printf("AMEX\n");
    }
    else if (CharNum == 15 && twoNumbers == 37 && atlikums == 0)
    {
        printf("AMEX\n");
    }
    else if (CharNum == 16 && twoNumbers == 51 && atlikums == 0)
    {
        printf("MASTERCARD\n");
    }
    else if (CharNum == 16 && twoNumbers == 52 && atlikums == 0)
    {
        printf("MASTERCARD\n");
    }
    else if (CharNum == 16 && twoNumbers == 53 && atlikums == 0)
    {
        printf("MASTERCARD\n");
    }
    else if (CharNum == 16 && twoNumbers == 54 && atlikums == 0)
    {
        printf("MASTERCARD\n");
    }
    else if (CharNum == 16 && twoNumbers == 55 && atlikums == 0)
    {
        printf("MASTERCARD\n");
    }
    else if (CharNum == 13 && oneNumber == 4 && atlikums == 0)
    {
        printf("VISA\n");
    }
    else if (CharNum == 16 && oneNumber == 4 && atlikums == 0)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}