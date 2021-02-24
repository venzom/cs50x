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
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Count the number of rounds
int process = -1;

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

    // Test to check for vote update
    /*tabulate();
    for (int l = 0; l < candidate_count; l++)
        {
            printf("%s %i\n", candidates[l].name, candidates[l].votes);
        }
    print_winner();


     // Test to check each section in preferences array
    for (int k = 0; k < voter_count; k++)
    {
        for (int l = 0; l < candidate_count; l++)
        {
            printf("%i ", preferences[k][l]);
        }
        printf("\n");
    }*/
    // tabulate();
    // print_winner();
    // int min = find_min();
    // is_tie(min);

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
    // Update preferences
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Update vote count for each cadidate by using preferences[i][0]
    process++;
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (j == preferences[i][0] && candidates[j].eliminated == false)
            {
                candidates[j].votes++;
            }
            else if (candidates[j].eliminated == true)
            {
                if (j == preferences[i][process])
                {
                    candidates[process].votes++;
                }
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Calculate the minimum number of votes required to win
    // and print winner if there is one
    int win = voter_count / 2;
    //printf("Win %i", win);
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > win)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Arrange votes from smallest[0] to largest and return smallest(min)
    int min = 0;
    for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[0].votes > candidates[i].votes && candidates[i].eliminated == false)
            {
                candidates[0] = candidates[i];
            }
        }
    min = candidates[0].votes;
    //printf("Min %i\n", min);
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int count = 0;
    int remaining = candidate_count;
    // Run through each candidate and check if votes is equal to min
    // and still in the race and also track remaining candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && candidates[i].eliminated == false)
        {
            count++;
        }
        else if (candidates[i].eliminated == true)
        {
            remaining--;
        }
    }
    // printf("count %i rem %i ", count, remaining);
    // Check if the amount of candidates with the minimum vote is equal to
    // candidates still in race, if yes return true, else false
    if (count == remaining)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // 
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
