#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // find the elector
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            // update the preferences of the voter
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // update the votes counts for each of the non-eliminated candidates
    for (int voter = 0; voter < voter_count; voter++)
    {
        int topChoice = 0;

        // foreach voter add votes based on their preferences
        for (int currentCan = 0; currentCan < candidate_count; currentCan++)
        {
            int preferred = preferences[voter][topChoice];
            if (candidates[preferred].eliminated)
            {
                topChoice++;
                continue;
            }

            candidates[preferred].votes++;
            break;
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // if any candidate has more than half of the vote, their name should be printed and return true
    float halfVotes = (float) voter_count / 2;
    int winnerIndex = -1;
    int winnerVotes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        candidate current = candidates[i];
        if (current.eliminated)
        {
            // skip eliminated
            continue;
        }

        int currentVotes = current.votes;
        if (currentVotes > halfVotes)
        {
            winnerIndex = i;
            break;
        }
        else if (currentVotes == halfVotes)
        {
            return false;
        }
    }

    if (winnerIndex >= 0)
    {
        printf("%s\n", candidates[winnerIndex].name);
        return true;
    }

    // if nobody has won the election yet, return false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // keep track of min
    // set to the max number of voters first and deduce
    int min = voter_count;

    // loop through candidates and see who has the min
    for (int i = 0; i < candidate_count; i++)
    {
        // update the min as we loop through the candidates
        // skip min check if eliminated
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }

    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // finding a tie could essentially also mean if there is not a max
    // since we have a min we can loop through the candidates and find the max

    int maxVoteCount = min;
    int tieCounter = 0;
    int eliminatedCounter = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        candidate current = candidates[i];
        if (current.eliminated)
        {
            eliminatedCounter++;
            continue;
        }

        if (current.votes > maxVoteCount)
        {
            maxVoteCount = current.votes;
            tieCounter = 0;
        }
        else if (current.votes == maxVoteCount)
        {
            tieCounter++;
        }
    }

    return eliminatedCounter + tieCounter == candidate_count;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // loop through the candidates and find the one where their votes is equal to min
    // mark the candidate with the min votes as eliminated
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated)
        {
            continue;
        }

        if (candidates[i].votes <= min)
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}
