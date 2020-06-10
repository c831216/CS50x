#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#define MAX_LIMIT 2000

int main()
{
    char str[MAX_LIMIT]; 
    printf("Text: ");
    fgets(str, MAX_LIMIT, stdin);
    // printf("\nThis is what you entered:\nText: %s", str);
    double letters = 0;
    double words = 0;
    double sentences = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        if (isalpha(str[i]))
        {
            letters++;
        }
        if (str[i] == ' ' || str[i] == '\r')
        {
            words++;
        }
        if (str[i] == '.' || str[i] == '!' || str[i] == '?')
        {
            sentences++;
        }
        i++;
    }

    // printf("\n%f letter(s)\n%f words(s)\n%f sentence(s)\n", letters, words + 1, sentences);
    
    words = words + 1;
    
    //L = Letters ÷ Words × 100 
    float L = letters / words * 100;
    // printf("The L = %f", L);
    
    
    //S = Sentences ÷ Words × 100
    float S = sentences / words * 100;
    // printf("The S = %f\n", S);
    
    //CLI = 0.0588 x L - 0.296 x S - 15.8
    float CLI = (0.0588 * L) - (0.296 * S) - 15.8;
    
    // printf("%f", CLI);
    
    int index;
    index = round(CLI);
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    if (index >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else
    {
        printf("Grade %d\n", index);
        return 0;
    }
}
