#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string getInput(int playerId);
int decide_winner(string p1, string p2);
int compute_score(string input);

const int TIE_ID = 0;
const int PLAYER1_ID = 1;
const int PLAYER2_ID = 2;
const string PLAYER1 = "Player 1";
const string PLAYER2 = "Player 2";
const int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // get inputs for player one and player two
    string p1Input = getInput(PLAYER1_ID);
    string p2Input = getInput(PLAYER2_ID);

    // calculate the score for each letter from both inputs
    int winner = decide_winner(p1Input, p2Input);

    // print out the player for the higher of the two
    //  0 = TIE_ID, 1 = PLAYER1_ID, 2 = PLAYER2_ID
    switch (winner) {
        case PLAYER1_ID:
            printf("%s wins!\n", PLAYER1);
            break;
        case PLAYER2_ID:
            printf("%s wins!\n", PLAYER2);
            break;
        default:
            printf("Tie!\n");
            break;
    }
}

string getInput(int playerId)
{
    string player = playerId == PLAYER1_ID ? "Player 1" : "Player 2";

    string input = "";
    do
    {
        input = get_string("%s: ", player);
    }
    while (strcmp(input, "") == 0);

    return input;
}

int decide_winner(string p1, string p2)
{
    // Player 1 Calculation
    int p1Score = compute_score(p1);

    // Player 2 Calculation
    int p2Score = compute_score(p2);

    int result = p1Score > p2Score ? PLAYER1_ID : p2Score > p1Score ? PLAYER2_ID : TIE_ID;

    return result;
}

int compute_score(string input)
{
    int totalScore = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        // get the first character
        char currentChar = input[i];
        bool notAValidLetter = (currentChar <= 'a' && currentChar >= 'z') ||
                               (currentChar <= 'A' && currentChar >= 'Z');
        if (notAValidLetter) // only assign points if the current character is a valid character
        {
            continue;
        }

        if (isupper(currentChar))
        {
            totalScore += POINTS[currentChar - 'A'];
        }
        else if (islower(currentChar))
        {
            totalScore += POINTS[currentChar - 'a'];
        }
    }

    return totalScore;
}
