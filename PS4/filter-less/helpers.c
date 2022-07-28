#include "helpers.h"
#include <math.h>
#include <cs50.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Calculate the average color value
            image[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            //Copy value from blue into other colors
            image[i][j].rgbtRed = image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][j].rgbtBlue;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Get all the original colors
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            //Calculate the sepia values
            int sepiaRed = round((float).393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round((float).349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round((float).272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            //Write the sepia values. If sepia value larger than 255, write 255
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmpImage[height][width];
    //Make a copy of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            tmpImage[i][j].rgbtBlue = image[i][j].rgbtBlue;
            tmpImage[i][j].rgbtRed = image[i][j].rgbtRed;
            tmpImage[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }
    //Write reflection by copying values from copy to real image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            image[i][j].rgbtBlue = tmpImage[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtRed = tmpImage[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = tmpImage[i][width - j - 1].rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmpImage[height][width];
    //Make a copy of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            tmpImage[i][j].rgbtBlue = image[i][j].rgbtBlue;
            tmpImage[i][j].rgbtRed = image[i][j].rgbtRed;
            tmpImage[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }
    //Get every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float n = 0;
            int sRed = 0;
            int sGreen = 0;
            int sBlue = 0;
            //Get the pixels around the main pixel
            for (int k = 0; k < 3; k++)
            {
                for (int a = 0; a < 3; a++)
                {
                    //If the pixel is not out of the range add its value to sum
                    if (i - 1 + k >= 0 && j - 1 + a >= 0 && i - 1 + k < height &&  j - 1 + a < width)
                    {
                        n++;
                        sRed = sRed + tmpImage[i - 1 + k][j - 1 + a].rgbtRed;
                        sGreen = sGreen + tmpImage[i - 1 + k][j - 1 + a].rgbtGreen;
                        sBlue = sBlue + tmpImage[i - 1 + k][j - 1 + a].rgbtBlue;
                    }
                }
            }
            //Calculate average value
            int avgRed = round((float)sRed / n);
            int avgGreen = round((float)sGreen / n);
            int avgBlue = round((float)sBlue / n);
            //Write average value
            image[i][j].rgbtRed = avgRed;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtBlue = avgBlue;
        }
    }
    return;
}
