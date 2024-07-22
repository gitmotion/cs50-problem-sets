#include <cs50.h>
#include <stdio.h>

int getHeightInput();
void printBlock(int n);
void printLeftPyramid(int numOfSpaces, int numOfBlocks);

int main(void)
{
    // Prompt user for height
    int height = getHeightInput();

    // Create blocks by the number of times of the input
    int leftPyramidSpaces = height - 1;
    for (int i = 0; i < height; i++)
    {
        // print left pyramid
        printLeftPyramid(leftPyramidSpaces, i);

        // print space between pyramid
        printf("  ");

        // print right pryamid
        // since right doesn't need spaces before
        // we can just print the number of blocks
        printBlock(i);

        // print next line
        printf("\n");

        // decrement first spaces
        leftPyramidSpaces--;
    }
}

int getHeightInput()
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8); // Only accepts integer values 1-8

    return height;
}

void printBlock(int n)
{
    for (int i = 0; i <= n; i++)
    {
        printf("#");
    }
}

void printLeftPyramid(int numOfSpaces, int numOfBlocks)
{
    // print spaces of left pyramid
    for (int i = 0; i < numOfSpaces; i++)
    {
        printf(" ");
    }

    // print blocks of left pyramid
    printBlock(numOfBlocks);
}
