#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateArgs(int argc, string argv[]);
bool only_digits(string key);
string getInput();
string rotate(string text, int key);

int main(int argc, string argv[])
{
    // must accept a single line command argument
    int errorCode = validateArgs(argc, argv);
    if (errorCode != 0)
    {
        return errorCode;
    }

    // must ask for user input with plaintext:
    string plaintext = getInput();
    int key = atoi(argv[1]);

    // rotate plaintext with key
    string cipher = rotate(plaintext, key);

    // output ciphertext:  with the coresponding cipher
    // preserve casing
    printf("ciphertext: %s\n", cipher);

    return 0;
}

int validateArgs(int argc, string argv[])
{
    // it should print an error if the program is executed without an argument and return 1
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string key = argv[1];
    bool isValidKey = only_digits(key);
    if (!isValidKey)
    {
        // if the argument does not contain a decimal digit then it should return with a errorcode 1
        printf("Usage: ./caesar key\n");
        return 1;
    }

    return 0;
}

bool only_digits(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isdigit(key[i]))
        {
            return false;
        }
    }

    return true;
}

string getInput()
{
    string input = "";
    do
    {
        input = get_string("plaintext:  ");
    }
    while (strcmp(input, "") == 0);

    return input;
}

string rotate(string text, int key)
{
    int length = strlen(text);

    // allocate a char to store the values
    char *cipher = (char *) malloc((length + 1) * sizeof(char));

    for (int i = 0; i < length; i++)
    {
        // get the current character
        char current = text[i];

        // get its alphabetical representation as an int
        bool isCurrentUpper = isupper(current);
        int currentCharIntVal = isCurrentUpper ? current - 'A' : current - 'a';

        // if not a letter then just assign the value
        if (!isalpha(current))
        {
            cipher[i] = current;
            continue;
        }

        // formula for getting the rotated value
        // cipher = (plaintextAlphaValue + key) % 26
        // this will get the new position in the alphabet
        // then convert that to the corresponding ascii value
        char rotated = (currentCharIntVal + key) % 26;
        cipher[i] = isCurrentUpper ? rotated + 'A' : rotated + 'a';
    }

    // convert cipher to a string
    cipher[length] = '\0';
    return cipher;
}
