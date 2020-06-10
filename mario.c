#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int main(void)  //Testing Comments Test
{
    int i = 0;

    while (i < 1 || i > 8)  //This is making sure that we get the correct input
    {
        i = get_int("Height: "); //Testing Comments Test
        if (isdigit(i))
        {
            break;
        }
    }

    int x;
    int y;
    x = i * 2 + 2;
    y = i;
    int disp[y][x];
    int j;

    for (i = 0; i < y; i++) //This is where we filling in our 2D array with blanks
    {
        for (j = 0; j < x; j++) //Testing Comments Test
        {
            disp[i][j] = 0;
        }
    }
    int half1 = (x / 2) - 1;
    int half2 = half1 + 1;

    //counters are used to know how many from mids need to be filled in
    int counter = 0;

    while (counter < y) //Testing Comments Test
    {
        int e = 1;
        int hashes = counter + 1;
        while (hashes > 0)
        {
            disp[counter][half1 - e] = 1;
            disp[counter][half2 + e] = 1;
            hashes--;
            e++;
        }
        //printf("\nEND OF ROW %d", counter);
        counter++;  //onto next row
    }

    for (i = 0; i < y; i++) //This trims while it prints
    {
        for (j = 0; j < half2 + i + 2; j++)
        {
            if (disp[i][j] == 1) //Testing Comments Test
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
            if (j == half2 + i + 1) //Testing Comments Test
            {
                printf("\n");
            }
        }
    }
    return 0;
}
