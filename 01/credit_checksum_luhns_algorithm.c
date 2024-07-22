#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validateCCN(long ccn, bool *isAmex, bool *isVisa, bool *isMasterCard);
bool checksum(long ccn);
char *convertCCNToString(long ccn);

int main(void)
{
    // prompt the user for a credit card number
    long creditCardNumber = get_long("Number: ");

    // validate ccn / early return
    bool isAmex = false;
    bool isVisa = false;
    bool isMasterCard = false;
    bool isValid = validateCCN(creditCardNumber, &isAmex, &isVisa, &isMasterCard);
    if (!isValid)
    {
        printf("INVALID\n");
        return 0;
    }

    // checksum / early return
    bool isValidCheckSum = checksum(creditCardNumber);
    if (!isValidCheckSum)
    {
        printf("INVALID\n");
        return 0;
    }

    if (isAmex)
    {
        printf("AMEX\n");
    }
    else if (isVisa)
    {
        printf("VISA\n");
    }
    else if (isMasterCard)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

bool validateCCN(long ccn, bool *isAmex, bool *isVisa, bool *isMasterCard)
{
    // check length
    char *ccnStr = convertCCNToString(ccn);
    int ccnLength = strlen(ccnStr);

    bool isAmexLength = ccnLength == 15;
    bool isVisaLength = ccnLength == 13 || ccnLength == 16;
    bool isMasterCardLength = ccnLength == 16;
    if (!isAmexLength && !isVisaLength && !isMasterCardLength)
    {
        // AMEX = 15 digits starts with 34 or 37
        // MasterCard = 16 digits, starts with 51, 52, 53, 54, or 55
        // VISA = 13 or 16 digits, starts with 4
        return false;
    }

    // check starting numbers
    char firstChar = ccnStr[0];
    char secondChar = ccnStr[1];
    // AMEX = 15 digits starts with 34 or 37
    if (isAmexLength)
    {
        bool isAmexStartDigits = firstChar == '3' && (secondChar == '4' || secondChar == '7');
        if (isAmexStartDigits)
        {
            *isAmex = true;
            return true;
        }
    }

    // VISA = 13 or 16 digits, starts with 4
    if (isVisaLength && !*isAmex)
    {
        bool isVisaStartDigits = firstChar == '4';
        if (isVisaStartDigits)
        {
            *isVisa = true;
            return true;
        }
    }

    // MasterCard = 16 digits, starts with 51, 52, 53, 54, or 55
    if (isMasterCardLength && !*isAmex && !*isVisa)
    {
        bool isMasterCardStartDigits =
            firstChar == '5' && (secondChar == '1' || secondChar == '2' || secondChar == '3' ||
                                 secondChar == '4' || secondChar == '5');
        if (isMasterCardStartDigits)
        {
            *isMasterCard = true;
            return true;
        }
    }

    return false;
}

bool checksum(long ccn)
{
    // apply Luhn’s algorithm (checksum)
    // multiply every other digit by 2, then add those products' digits together
    // add the sum of the digits that weren't multipled by 2
    // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to
    // 0), the number is valid!

    // reverse loop through the string and multiply every second digit of the CCN
    // keep track of the sum of the multiplied digits and the other digits as well
    char *ccnStr = convertCCNToString(ccn);
    int ccnLength = strlen(ccnStr);
    int regularSum = 0;
    int multipliedSum = 0;
    for (int i = ccnLength - 1; i >= 0; i--)
    {
        char ccnChar = ccnStr[i];
        int ccnInt = ccnChar - '0';       // Convert char to int
        if ((ccnLength - 1 - i) % 2 == 1) // Every other digit starting from the right
        {
            int multipliedChar = ccnInt * 2;
            if (multipliedChar > 9)
            {
                // divide by 10 gives us the tenths place or the first digit
                // modulo 10 gives us the last digit / remainder
                multipliedSum += (multipliedChar / 10) + (multipliedChar % 10);
            }
            else
            {
                multipliedSum += multipliedChar;
            }
        }
        else // Digits that aren't multiplied by 2
        {
            regularSum += ccnInt;
        }
    }

    int totalSum = regularSum + multipliedSum;
    return (totalSum % 10 == 0);
}

char *convertCCNToString(long ccn)
{
    // firt allocate sufficient memory to hold the string representation
    char *ccnStr =
        malloc(20 * sizeof(char)); // Assuming a maximum of 19 digits for long + null terminator
    sprintf(ccnStr, "%ld", ccn);
    return ccnStr;
}
