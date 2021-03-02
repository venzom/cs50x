#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }
    for (int k = 0; k < candidate_count; k++)
    {
        for (int l = 0; l < candidate_count; l++)
        {
            printf("%i ", preferences[k][l]);
        }
        printf("\n");
    }
    add_pairs();
    for (int k = 0; k < pair_count; k++)
    {
        printf("Winner: %i Loser: %i\n", pairs[k].winner, pairs[k].loser);
    }
    sort_pairs();
    printf("-----\n");
    for (int k = 0; k < pair_count; k++)
    {
        printf("Winner: %i Loser: %i\n", pairs[k].winner, pairs[k].loser);
    }
    printf("Winner: %i \n", pairs[0].winner);
    lock_pairs();
    for (int k = 0; k < candidate_count; k++)
    {
        for (int l = 0; l < candidate_count; l++)
        {
            printf("%d ", locked[k][l]);
        }
        printf("\n");
    }
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Match candidate to array[i], if match, add rank to rank[]
    for (int i =0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Create array of preferences for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Compare each candidate to other at [i][i] or [j][j] find select
    // the largest preference.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Sort pairs using bubble sort by comparing vote count of winners
    for (int i = pair_count - 1; i >= 0; i--)
    {
        
        for (int j = 0; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                pair sort = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = sort;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Populate i x j array with true of winner, start with populating first pair
    if(pair_count > 0)
        locked[pairs[0].winner][pairs[0].loser] = true;
    // locked[pairs[1].winner][pairs[1].loser] = true;
    for (int i = 0; i < pair_count; i++)
        {
            bool check =  false;
            for (int j = 0; j < pair_count; j++)
            {
                if (locked[pairs[i].loser][j] == false)
                {
                    check = true;
                    break;
                }
            }
            // Check for cycle 
            if (check == false)
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
            
        }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

