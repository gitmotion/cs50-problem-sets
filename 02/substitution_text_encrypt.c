#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateKey(string key);
string getInput(string message);
string encrypt(string key, string message);

int main(int argc, string argv[])
{
    // validate args
    if (argc < 2)
    {
        printf("Usage ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    if (strlen(argv[1]) != 26 || argc > 2)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // validate key from the argument
    int errorCode = validateKey(key);
    if (errorCode != 0)
    {
        return errorCode;
    }

    // then ask for the plain text to encrypt
    string plaintext = getInput("plaintext");

    // encrypt the text using the key
    // make sure to preserve the casing and special characters
    string cipher = encrypt(key, plaintext);

    // then print the cypher text
    printf("ciphertext: %s\n", cipher);

    return 0;
}

int validateKey(string key)
{
    char seenChars[26] = {0};
    for (int i = 0, length = strlen(key); i < length; i++)
    {
        char current = key[i];
        int currentCharVal = isupper(current) ? current - 'A' : current - 'a';
        if (currentCharVal < 0 || currentCharVal > 25)
        {
            // return error code if special character
            // or not an alphabetical character
            return 1;
        }

        // check for duplicates
        for (int j = 0, n = i; j < n; j++)
        {
            char seen = seenChars[j];
            if (current == seen)
            {
                return 1;
            }
        }

        // mark as seen
        seenChars[i] = current;
    }

    return 0;
}

string getInput(string message)
{
    string input = "";
    do
    {
        input = get_string("%s: ", message);
    }
    while (strcmp(input, "") == 0);

    return input;
}

string encrypt(string key, string message)
{
    int length = strlen(message);
    char *cipher = (char *) malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; i++)
    {
        // get value of current character
        char current = message[i];
        if ((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z'))
        {
            // match to the key table
            int currentIntVal = isupper(current) ? current - 'A' : current - 'a';
            char matched = key[currentIntVal];
            cipher[i] = isupper(current) ? toupper(matched) : tolower(matched);
        }
        else
        {
            cipher[i] = current;
        }
    }

    cipher[length] = '\0';
    return cipher;
}
