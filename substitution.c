#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int arg_correct(char *argv[])
{
    //CHECK FOR VALID ARGUMENT STARTING WITH TESTING LENGTH
    int len = strlen(argv[1]);
    if (len == 26)
    {
        //ENSURE IT'S ONLY LETTERS
        int i = 0;
        while (argv[1][i])
        {
            if (isalpha(argv[1][i]))
            {
                i++;
            }
            else
            {
                printf("FOUND A NON-LETTER\n");
                return 1;
            }
        }
        //TEST FOR DUPLICATION
        i = 0;
        int j = 0;
        int counter = 0;
        char x;
        while (argv[1][i])
        {
            x = argv[1][i];
            j = 0;
            counter = 0;
            while (argv[1][j])
            {
                if (argv[1][j] == x)
                {
                    counter++;
                    if (counter > 1)
                    {
                        printf("DUPLICATE FOUND\n");
                        return 1;
                    }
                }
                j++;
            }
            i++;   
        }
    }
    else
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) 
{
    if (argc == 2)
    {
        //CHECK IF CORRECT ARG ENTERED
        if (arg_correct(argv) == 0)
        {
            string ptext = get_string("plaintext : ");
            int i = 0;
            char a;
            char b;
            char test;
            int alpha = 0;
            printf("ciphertext: ");
            while (ptext[i] != '\0')
            {
                a = ptext[i];
                
                if (a >= 'A' && a <= 'Z') //THIS IS DEF AN UPPERCASE LETTER
                {
                    alpha = ptext[i] - 65;
                    b = argv[1][alpha];
                    if (b >= 'A' && b <= 'Z') //IT'S UPPERCASE PRINT
                    {
                        printf("%c", b);
                    }
                    else
                    {
                        printf("%c", b - 32); //MAKE UPPERCASE THEN PRINT
                    }
                }
                else if (a >= 'a' && a <= 'z') //THIS IS DEF A  LOWERCASE LETTER
                {
                    alpha = ptext[i] - 97;
                    b = argv[1][alpha];
                    if (b >= 'a' && b <= 'z') //IT'S LOWERCASE PRINT
                    {
                        printf("%c", b);
                    }
                    else
                    {
                        printf("%c", b + 32); //MAKE LOWERCASE THEN PRINT
                    }
                }
                else
                {
                    printf("%c", a);
                }
                i++;
            }
            printf("\n");
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        printf("Usage: %s key\n", argv[0]);
    }
    
    return 1;
}

//I made a mistake in removing some comments to be able to
//better read my code.
//So here we go lets see how many more comments are needed
