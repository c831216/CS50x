#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9 // Max number of candidates

typedef struct // Candidates have name and vote count
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];// Array of candidates
int candidate_count; //Number of candidates
bool vote(string name); //Function Prototype
void print_winner(void); //Function Prototype

int main(int argc, string argv[])
{
    if (argc < 2) // Check for invalid usage
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1; // Populate array of candidates
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++) //Loop over all voters
    {
        string name = get_string("Vote: ");

        if (!vote(name)) //Check for invalid vote
        {
            printf("Invalid vote.\n");
            // i--;
        }
    }

    print_winner(); //Display winner of election
}

bool vote(string name) //Update vote totals given a new vote
{
    int i = 0;
    while (i < candidate_count)
    {
        int j = 0;
        while (j < candidate_count)
        {
            if ((strcmp(name, candidates[j].name)) == 0)
            {
                candidates[j].votes++;
                return true;
            }
            j++;
        }
        i++;
    }
    return false;
}

void print_winner(void) // Print the winner (or winners) of the election
{
    //find highest
    int highest = 0;
    int i = 0;
    while (i < candidate_count)
    {
        if (candidates[i].votes > highest)
        {
            highest = candidates[i].votes;
        }
        i++;
    }
    //then if name.votes == highets print
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == highest)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
