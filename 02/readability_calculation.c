#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

string get_input();
int count_letters(string s);
int count_words(string s);
int count_sentences(string s);
float compute_index(int letterCount, int wordCount, int sentenceCount);

int main(void)
{
    // prompt the user for a block of text
    string input = get_input();

    // count the number of letters, words, and sentences in the text
    int letterCount = count_letters(input);
    int wordCount = count_words(input);
    int sentenceCount = count_sentences(input);

    // compute the Coleman-Liau index
    float index = compute_index(letterCount, wordCount, sentenceCount);

    // print the grade level
    if (index >= 16.0)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1.0)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}

string get_input()
{
    string input = "";
    do
    {
        input = get_string("Text: ");
    }
    while (strcmp(input, "") == 0);

    return input;
}

int count_letters(string s)
{
    int count = 0;

    for (int i = 0, length = strlen(s); i < length; i++)
    {
        char currentChar = s[i];
        if ((currentChar >= 'a' && currentChar <= 'z') ||
            (currentChar >= 'A' && currentChar <= 'Z'))
        {
            count++;
        }
    }

    return count;
}

int count_words(string s)
{
    // to count the words we can count the amount of spaces + 1;
    int count = 0;
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        char currentChar = s[i];
        if (currentChar == ' ')
        {
            count++;
        }
    }

    // This is to account for the word after the last space
    count++;

    return count;
}

int count_sentences(string s)
{
    // To count amount of sentences, we can count the amount of punctuations
    int count = 0;
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        char currentChar = s[i];
        if (currentChar == '.' || currentChar == '!' || currentChar == '?')
        {
            count++;
        }
    }

    return count;
}

float compute_index(int letterCount, int wordCount, int sentenceCount)
{
    // L is the average number of letters per 100 words in the text: that is, the number of letters
    // divided by the number of words, all multiplied by 100. S is the average number of sentences
    // per 100 words in the text: that is, the number of sentences divided by the number of words,
    // all multiplied by 100. You’ll want to round the result to the nearest whole number, so recall
    // that round is declared in math.h, per manual.cs50.io.
    float L = ((float) letterCount / wordCount) * 100;
    float S = ((float) sentenceCount / wordCount) * 100;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    return round(index);
}
