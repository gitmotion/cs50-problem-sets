#include <cs50.h>
#include <stdio.h>

int getChangePrompt();
int calculateAmount(int cents, int coinAmount);

int main(void)
{
    // prompt user for change amount
    int cents = getChangePrompt();

    // there should be 4 coins
    // quarters, dimes, nickels, pennies
    const int quarterValue = 25;
    const int dimeValue = 10;
    const int nickelValue = 5;
    const int pennyValue = 1;

    // early return
    int countOfCoins = 0;
    if (cents > 0)
    {
        // first calculate how many quarters (if any) to give to the customer and subtract that from
        // the amount
        int quarters = calculateAmount(cents, quarterValue);
        cents = cents - (quarterValue * quarters);

        // then calculate how many dimes (if any) and subtract that from the amount
        int dimes = calculateAmount(cents, dimeValue);
        cents = cents - (dimeValue * dimes);

        // then calculate how many nickels (if any) and subtract that from the amount
        int nickels = calculateAmount(cents, nickelValue);
        cents = cents - (nickelValue * nickels);

        // then calculate how many pennies (if any)
        int pennies = calculateAmount(cents, pennyValue);

        // then sum the amount of coins used to make the amount
        countOfCoins = quarters + dimes + nickels + pennies;
    }

    // finally print that amount
    printf("%i\n", countOfCoins);
}

int getChangePrompt()
{
    int amount;
    do
    {
        amount = get_int("Change owed: ");
    }
    while (amount < 0);

    return amount;
}

int calculateAmount(int cents, int coinAmount)
{
    int countOfCoins = 0;

    // early return
    // add check here to reduce amount of check in the parent scope
    if (cents < coinAmount)
    {
        return countOfCoins;
    }

    while (cents >= coinAmount)
    {
        countOfCoins++;
        cents = cents - coinAmount;
    }

    return countOfCoins;
}
