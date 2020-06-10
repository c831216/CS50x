#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int test(char *num)
{
    // printf("ENTERED: %s\n", num);
    //Lets implement the Luhn’s Algorithm
    int numlen = strlen(num);
    int arrayZero[numlen];
    
    int i = 0;
    while (i < numlen)
    {
        //need to convert num to ints
        arrayZero[i] = num[i] - 48;
        // printf("\nTESTING %d", arrayZero[i]);
        i++;
    }

    int arrayOne[numlen];
    int array_two[numlen];
    i = 0;
    // printf("\nThe amount of digits entered: %d\n", numlen);
    int start = numlen;
    int how_big_one = 0;
    int how_big_two = 0;
    while (start > 0)
    {
        // printf("\nTESTING %d",arrayOne[i]);
        start -= 1;
        array_two[i] = arrayZero[start];
        how_big_two++;
        if (start > 0)
        {
            start -= 1;
        }
        else
        {
            break;
        }
        arrayOne[i] = arrayZero[start] * 2; //I'm right here :)
        how_big_one++;
        
        i++;   
    }
    // printf("This is arrayOne %d", arrayOne[0]);
    // how_big_one = i;
    // for(i = 0; i < how_big_one; i++){printf("-> %d", arrayOne[i]);}
    // printf("\n");
    // for(i = 0; i < how_big_two; i++){printf("-> %d", array_two[i]);}
    // printf("THIS IS howBig = %d", howBig);
    //I need to get the digits alone, create string
    // int a[5]={5,21,456,1,3}; // this is arrayOne
    char s[10000] = {0};
    int n = 0;

    for (i = 0; i <= how_big_one; i++) 
    {
        // printf("\nWTF? this is i = %d and this is arrayOne at i = %d", i,arrayOne[i]);
        n += sprintf(&s[n], "%d", arrayOne[i]);
    }

    // printf ("\n digit string = %s\n\n", s);
    int sumof = 0;
    int slen = strlen(s);
    for (i = 0; i < slen; i++)
    {
        sumof = sumof + (s[i] - 48);
    }
    // printf("\n char* s = %s\n\n", digiAlone);
    //split to int digits
    //then I need to add up each digit
    // printf("\nTHIS IS SUMOF %d", sumof);
    //add sumof to others not multiplied by 2
    // printf("\nTHIS IS ARRAY_TWO %d", array_two[0]);

    //lets try and add them together
    int sumof_two = sumof;
    for (i = 0; i < how_big_two; i++)
    {
        sumof_two = sumof_two + array_two[i];
    }
    // printf("\nIs this the sum of two? %d\n", sumof_two);
    
    // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    // Add the sum to the sum of the digits that weren’t multiplied by 2.
    // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!

    if (sumof_two % 10 == 0)
    {
        return 1;
    } 
    else 
    {
        return 0;
    }
    // return 1; //if true return 1 if false return 0

}

int main()
{
    long num;
    char snum [sizeof(num)];
    num = get_long("Number: ");
    sprintf(snum, "%ld", num);

    if (test(snum) == 0)
    {
        printf("INVALID\n");
        return 0;
    }

    //printf("You entered: %s\n", snum);
    if (strlen(snum) > 0)
    {
        // American Express uses 15-digit numbers, start with 34 or 37
        if (strlen(snum) == 15)
        {
            //printf("%lu\n", (strlen(snum)));
            //printf("first digit %c, second digit %c\n", snum[0], snum[1]);
            if ((snum[0] == '3' && snum[1] == '4') || (snum[0] == '3' && snum[1] == '7'))
            {
                if (test(snum))
                {
                    printf("AMEX\n");
                }
                return 0;
            }
        }
        // Visa uses 13- and 16-digit numbers, start with 4
        if (strlen(snum) == 16 || strlen(snum) == 13)
        {
            if (snum[0] == '4')
            {
                //VISA
                if (test(snum))
                {
                    printf("VISA\n");
                }
                return 0;
            }
            else if ((snum[0] == '5') && ((snum[1] == '1') || 
                                          (snum[1] == '2') || 
                                          (snum[1] == '3') ||
                                          (snum[1] == '4') || 
                                          (snum[1] == '5')))
                // MasterCard uses 16-digit numbers, start with 51, 52, 53, 54, or 55
            {
                //MASTERCARD
                if (test(snum))
                {
                    printf("MASTERCARD\n");
                }
                return 0;
            }
        }
        printf("INVALID\n");
    }
    return 0;
}
 
