#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>



int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Geting text
    string text = get_string("Text:");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    //Calculating index
    int index = round(0.0588 * 100 * letters / words - 0.296 * 100 * sentences / words - 15.8);
    //Printing the grade
    if (1 < index && index < 16)
    {
        printf("Grade %d\n", index);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }

}
//Counting the number of letters in text
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((64 < text[i] && text[i] < 91) || (96 < text[i] && text[i] < 123))
        {
            letters++;
        }
    }
    return letters;
}
//Counting the number of words in text
int count_words(string text)
{
    int words = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 32)
        {
            words++;
        }
    }
    return words;
}
//Counting the number of sentences in text
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}