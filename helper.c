#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// char* itoa(int, RGBTRIPLE , int);

// Convert image to grayscale

// Grayscale

// One common filter is the “grayscale” filter, where we take an image and want to convert it to black-and-white. 
// How does that work?

// Recall that if the red, green, and blue values are all set to 0x00 (hexadecimal for 0), then the pixel is black. 
// And if all values are set to 0xff (hexadecimal for 255), then the pixel is white. So long as the red, green, and 
// blue values are all equal, the result will be varying shades of gray along the black-white spectrum, with higher 
// values meaning lighter shades (closer to white) and lower values meaning darker shades (closer to black).

// So to convert a pixel to grayscale, we just need to make sure the red, green, and blue values are all the same 
// value. But how do we know what value to make them? Well, it’s probably reasonable to expect that if the original 
// red, green, and blue values were all pretty high, then the new value should also be pretty high. And if the 
// original values were all low, then the new value should also be low.

// In fact, to ensure each pixel of the new image still has the same general brightness or darkness as the old 
// image, we can take the average of the red, green, and blue values to determine what shade of grey to make the 
// new pixel.

// If you apply that to each pixel in the image, the result will be an image converted to grayscale.
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int b, g, r;
    float avg;

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            b = image[i][k].rgbtBlue;
            g = image[i][k].rgbtGreen;
            r = image[i][k].rgbtRed;
            avg = round((b + g + r) / 3.00);
            
            image[i][k].rgbtBlue = avg;
            image[i][k].rgbtGreen = avg;
            image[i][k].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;
    
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            sepiaRed = round(.393 * image[i][k].rgbtRed + .769 * image[i][k].rgbtGreen + .189 * image[i][k].rgbtBlue);
            sepiaGreen = round(.349 * image[i][k].rgbtRed + .686 * image[i][k].rgbtGreen + .168 * image[i][k].rgbtBlue);
            sepiaBlue = round(.272 * image[i][k].rgbtRed + .534 * image[i][k].rgbtGreen + .131 * image[i][k].rgbtBlue);
            
            if (sepiaRed > 255)
            {
                image[i][k].rgbtRed = 255;
            }
            else
            {
                image[i][k].rgbtRed = sepiaRed;
            }
            
            if (sepiaGreen > 255)
            {
                image[i][k].rgbtGreen = 255;
            }
            else
            {
                image[i][k].rgbtGreen = sepiaGreen;
            }
            
            if (sepiaBlue > 255)
            {
                image[i][k].rgbtBlue = 255;
            }
            else
            {
                image[i][k].rgbtBlue = sepiaBlue;
            }
        }
    }
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int x;
    // RGBTRIPLE temp_image[height][width];
    RGBTRIPLE(*temp_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    
    for (int i = 0; i < height; i++) //Store in temp
    {
        x = width - 1;
        for (int k = 0; k < width; k++)
        {
            // temp_image[y][x] = image[i][k];
            temp_image[i][k].rgbtRed   = image[i][x].rgbtRed;
            temp_image[i][k].rgbtGreen = image[i][x].rgbtGreen;
            temp_image[i][k].rgbtBlue  = image[i][x].rgbtBlue;
            x = x - 1;
        }
    }
    
    for (int i = 0; i < height; i++) //Move from temp
    {
        for (int k = 0; k < width; k++)
        {
            // image[i][k] = temp_image[i][k];
            image[i][k].rgbtRed   = temp_image[i][k].rgbtRed;
            image[i][k].rgbtGreen = temp_image[i][k].rgbtGreen;
            image[i][k].rgbtBlue  = temp_image[i][k].rgbtBlue;
        }
    }
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Lets go through the logic
    RGBTRIPLE ti[height][width];
    double d, r, b, g;
    
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            ti[i][k] = image[i][k];
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            d = 0.0;
            r = 0.0;
            b = 0.0;
            g = 0.0;
            if (i == 0 && k == 0) //Top left
            {
                // printf("\nTOP LEFT\n");
                r = r + ti[i][k].rgbtRed;
                b = b + ti[i][k].rgbtBlue;
                g = g + ti[i][k].rgbtGreen;
                d++;
                r = r + ti[i][k + 1].rgbtRed;
                b = b + ti[i][k + 1].rgbtBlue;
                g = g + ti[i][k + 1].rgbtGreen;
                d++;
                r = r + ti[i + 1][k].rgbtRed;
                b = b + ti[i + 1][k].rgbtBlue;
                g = g + ti[i + 1][k].rgbtGreen;
                d++;
                r = r + ti[i + 1][k + 1].rgbtRed;
                b = b + ti[i + 1][k + 1].rgbtBlue;
                g = g + ti[i + 1][k + 1].rgbtGreen;
                d++;
                // printf("\n %f", d);
            }
            if (i == 0 && k > 0 && k < width - 1) //Top row
            {
                // printf("\nTOP ROW\n");
                r = r + ti[i][k - 1].rgbtRed;
                b = b + ti[i][k - 1].rgbtBlue;
                g = g + ti[i][k - 1].rgbtGreen;
                d++;
                r = r + ti[i][k].rgbtRed;
                b = b + ti[i][k].rgbtBlue;
                g = g + ti[i][k].rgbtGreen;
                d++;
                r = r + ti[i][k + 1].rgbtRed;
                b = b + ti[i][k + 1].rgbtBlue;
                g = g + ti[i][k + 1].rgbtGreen;
                d++;
                r = r + ti[i + 1][k - 1].rgbtRed;
                b = b + ti[i + 1][k - 1].rgbtBlue;
                g = g + ti[i + 1][k - 1].rgbtGreen;
                d++;
                r = r + ti[i + 1][k].rgbtRed;
                b = b + ti[i + 1][k].rgbtBlue;
                g = g + ti[i + 1][k].rgbtGreen;
                d++;
                r = r + ti[i + 1][k + 1].rgbtRed;
                b = b + ti[i + 1][k + 1].rgbtBlue;
                g = g + ti[i + 1][k + 1].rgbtGreen;
                d++;
                // printf("\n %f", d);
            }
            if (i == 0 && k == width - 1) //Top right
            {
                // printf("\nTOP RIGHT\n");
                r = r + ti[i][k].rgbtRed;
                b = b + ti[i][k].rgbtBlue;
                g = g + ti[i][k].rgbtGreen;
                d++;
                r = r + ti[i][k - 1].rgbtRed;
                b = b + ti[i][k - 1].rgbtBlue;
                g = g + ti[i][k - 1].rgbtGreen;
                d++;
                r = r + ti[i + 1][k].rgbtRed;
                b = b + ti[i + 1][k].rgbtBlue;
                g = g + ti[i + 1][k].rgbtGreen;
                d++;
                r = r + ti[i + 1][k - 1].rgbtRed;
                b = b + ti[i + 1][k - 1].rgbtBlue;
                g = g + ti[i + 1][k - 1].rgbtGreen;
                d++;
                // printf("\n %f", d);
            }
            if (k == 0 && i > 0 && i < height - 1) //Left side
            {
                // printf("\nLEFT SIDE\n");
                r = r + ti[i - 1][k].rgbtRed;
                b = b + ti[i - 1][k].rgbtBlue;
                g = g + ti[i - 1][k].rgbtGreen;
                d++;
                r = r + ti[i - 1][k + 1].rgbtRed;
                b = b + ti[i - 1][k + 1].rgbtBlue;
                g = g + ti[i - 1][k + 1].rgbtGreen;
                d++;
                r = r + ti[i][k].rgbtRed;
                b = b + ti[i][k].rgbtBlue;
                g = g + ti[i][k].rgbtGreen;
                d++;
                r = r + ti[i][k + 1].rgbtRed;
                b = b + ti[i][k + 1].rgbtBlue;
                g = g + ti[i][k + 1].rgbtGreen;
                d++;
                r = r + ti[i + 1][k].rgbtRed;
                b = b + ti[i + 1][k].rgbtBlue;
                g = g + ti[i + 1][k].rgbtGreen;
                d++;
                r = r + ti[i + 1][k + 1].rgbtRed;
                b = b + ti[i + 1][k + 1].rgbtBlue;
                g = g + ti[i + 1][k + 1].rgbtGreen;
                d++;
                // printf("\n %f", d);
            }
            if (k == width - 1 && i > 0 && i < height - 1) //Right side
            {
                // printf("\nRIGHT SIDE\n");
                r = r + ti[i - 1][k - 1].rgbtRed;
                b = b + ti[i - 1][k - 1].rgbtBlue;
                g = g + ti[i - 1][k - 1].rgbtGreen;
                d++;
                r = r + ti[i - 1][k].rgbtRed;
                b = b + ti[i - 1][k].rgbtBlue;
                g = g + ti[i - 1][k].rgbtGreen;
                d++;
                r = r + ti[i][k - 1].rgbtRed;
                b = b + ti[i][k - 1].rgbtBlue;
                g = g + ti[i][k - 1].rgbtGreen;
                d++;
                r = r + ti[i][k].rgbtRed;
                b = b + ti[i][k].rgbtBlue;
                g = g + ti[i][k].rgbtGreen;
                d++;
                r = r + ti[i + 1][k - 1].rgbtRed;
                b = b + ti[i + 1][k - 1].rgbtBlue;
                g = g + ti[i + 1][k - 1].rgbtGreen;
                d++;
                r = r + ti[i + 1][k].rgbtRed;
                b = b + ti[i + 1][k].rgbtBlue;
                g = g + ti[i + 1][k].rgbtGreen;
                d++;
                // printf("\n %f", d);
            }
            if (i == height - 1 && k == 0) //Bottom left
            {
                // printf("\nBOTTOM LEFT\n");
                r = r + ti[i - 1][k].rgbtRed;
                b = b + ti[i - 1][k].rgbtBlue;
                g = g + ti[i - 1][k].rgbtGreen;
                d++;
                r = r + ti[i - 1][k + 1].rgbtRed;
                b = b + ti[i - 1][k + 1].rgbtBlue;
                g = g + ti[i - 1][k + 1].rgbtGreen;
                d++;
                r = r + ti[i][k].rgbtRed;
                b = b + ti[i][k].rgbtBlue;
                g = g + ti[i][k].rgbtGreen;
                d++;
                r = r + ti[i][k + 1].rgbtRed;
                b = b + ti[i][k + 1].rgbtBlue;
                g = g + ti[i][k + 1].rgbtGreen;
                d++;
                // printf("\n %f", d);
            }
            if (i == height - 1 && k > 0 && k < width - 1) // Bottom row
            {
                // printf("\nBOTTOM ROW\n");
                r = r + ti[i - 1][k - 1].rgbtRed;
                b = b + ti[i - 1][k - 1].rgbtBlue;
                g = g + ti[i - 1][k - 1].rgbtGreen;
                d++;
                r = r + ti[i - 1][k].rgbtRed;
                b = b + ti[i - 1][k].rgbtBlue;
                g = g + ti[i - 1][k].rgbtGreen;
                d++;
                r = r + ti[i - 1][k + 1].rgbtRed;
                b = b + ti[i - 1][k + 1].rgbtBlue;
                g = g + ti[i - 1][k + 1].rgbtGreen;
                d++;
                r = r + ti[i][k - 1].rgbtRed;
                b = b + ti[i][k - 1].rgbtBlue;
                g = g + ti[i][k - 1].rgbtGreen;
                d++;
                r = r + ti[i][k].rgbtRed;
                b = b + ti[i][k].rgbtBlue;
                g = g + ti[i][k].rgbtGreen;
                d++;
                r = r + ti[i][k + 1].rgbtRed;
                b = b + ti[i][k + 1].rgbtBlue;
                g = g + ti[i][k + 1].rgbtGreen;
                d++;
                // printf("\n %f", d);
            }
            if (i == height - 1 && k == width - 1) // Bottom right
            {
                // printf("\nBOTTOM RIGHT\n");
                r = r + ti[i - 1][k - 1].rgbtRed;
                b = b + ti[i - 1][k - 1].rgbtBlue;
                g = g + ti[i - 1][k - 1].rgbtGreen;
                d++;
                r = r + ti[i - 1][k].rgbtRed;
                b = b + ti[i - 1][k].rgbtBlue;
                g = g + ti[i - 1][k].rgbtGreen;
                d++;
                r = r + ti[i][k - 1].rgbtRed;
                b = b + ti[i][k - 1].rgbtBlue;
                g = g + ti[i][k - 1].rgbtGreen;
                d++;
                r = r + ti[i][k].rgbtRed;
                b = b + ti[i][k].rgbtBlue;
                g = g + ti[i][k].rgbtGreen;
                d++;
                // printf("\n %f", d);
            }
            if (i > 0 && k > 0 && i < height - 1 && k < width - 1) // Anywhere else
            {
                // printf("\nMIDDLE\n");
                r = r + ti[i - 1][k - 1].rgbtRed;
                b = b + ti[i - 1][k - 1].rgbtBlue;
                g = g + ti[i - 1][k - 1].rgbtGreen;
                d++;
                r = r + ti[i - 1][k].rgbtRed;
                b = b + ti[i - 1][k].rgbtBlue;
                g = g + ti[i - 1][k].rgbtGreen;
                d++;
                r = r + ti[i - 1][k + 1].rgbtRed;
                b = b + ti[i - 1][k + 1].rgbtBlue;
                g = g + ti[i - 1][k + 1].rgbtGreen;
                d++;
                r = r + ti[i][k - 1].rgbtRed;
                b = b + ti[i][k - 1].rgbtBlue;
                g = g + ti[i][k - 1].rgbtGreen;
                d++;
                r = r + ti[i][k].rgbtRed;
                b = b + ti[i][k].rgbtBlue;
                g = g + ti[i][k].rgbtGreen;
                d++;
                r = r + ti[i][k + 1].rgbtRed;
                b = b + ti[i][k + 1].rgbtBlue;
                g = g + ti[i][k + 1].rgbtGreen;
                d++;
                r = r + ti[i + 1][k - 1].rgbtRed;
                b = b + ti[i + 1][k - 1].rgbtBlue;
                g = g + ti[i + 1][k - 1].rgbtGreen;
                d++;
                r = r + ti[i + 1][k].rgbtRed;
                b = b + ti[i + 1][k].rgbtBlue;
                g = g + ti[i + 1][k].rgbtGreen;
                d++;
                r = r + ti[i + 1][k + 1].rgbtRed;
                b = b + ti[i + 1][k + 1].rgbtBlue;
                g = g + ti[i + 1][k + 1].rgbtGreen;
                d++;
                // printf("\n %f", d);
            }
            // printf("i = %i and k = %i", i, k);
            // printf("\nTHIS IS D = %f", d);
            image[i][k].rgbtRed = round(r / d);
            // printf("\nred = %hhu\n", image[i][k].rgbtRed);
            image[i][k].rgbtBlue = round(b / d);
            // printf("\nblue = %hhu\n", image[i][k].rgbtBlue);
            image[i][k].rgbtGreen = round(g / d);
            // printf("\ngreen = %hhu\n", image[i][k].rgbtGreen);
        }
    }
    return;
}
