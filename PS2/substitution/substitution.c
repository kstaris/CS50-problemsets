#include <cs50.h>
#include <stdio.h>
#include <string.h>

int replace_letter(char letter, string key);

int main(int argc, string argv[])
{
    if (argv[1] == NULL || argv[2])
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string key = argv[1];
    //Validate key
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 alhabetical characters.\n");
        return 1;
    }
    //Validate invalid characters
    int k = 0;
    int times = 0;
    for (k = 0; strlen(key) > k; k++)
    {
        if (key[k] < 65 || (90 < key[k] && key[k] < 97) || key[k] > 122)
        {
            printf("Invalid character\n");
            return 1;
        }
        //Validate multiple arguments
        for (int n = 0; strlen(key) > n; n++)
        {
            if (key[k] == key[n])
            {
                times++;
                if (times > 26)
                {
                    printf("Dublicate argument\n");
                    return 1;
                }
            }
        }
    }
    //Format key
    for (int i = 0; i < strlen(key); i++)
    {
        if (96 < key[i] && key[i] < 123)
        {
            key[i] = key[i] - 32;
        }
    }
    //Get plaintext
    string plText = get_string("plaintext:  ");
    //Chiper letters
    string chText = plText;
    printf("test = %s\n", chText);
    for (int i = 0; i < strlen(plText); i++)
    {
        if ((64 < plText[i] && plText[i] < 91) || (96 < plText[i] && plText[i] < 123))
        {
            chText[i] = replace_letter(plText[i], key);
        }
        else
        {
            chText[i] = plText[i];
        }
    }
    printf("ciphertext: %s\n", chText);
}

int replace_letter(char letter, string key)
{
    char chLetter;
    //Replace capital letter
    if (64 < letter && letter < 91)
    {
        int keyNum = letter - 65;
        printf("keyNum %d\n", keyNum);
        chLetter = key[keyNum];
    }
    //Replace lowercase letter
    if (96 < letter && letter < 123)
    {
        int keyNum = letter - 97;
        chLetter = key[keyNum] + 32;
    }
    return chLetter;
}