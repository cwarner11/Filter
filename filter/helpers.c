#include "helpers.h"
#include <math.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // column aka height
    {
        for (int j = 0; j < width; j++) // row aka width
        {
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            int avg_value = round(( (float) red + (float) blue + (float)  green) / 3);

            image[i][j].rgbtBlue = avg_value;
            image[i][j].rgbtRed  = avg_value;
            image[i][j].rgbtGreen  = avg_value;
        }
    }
 return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for ( int i = 0; i < height; i++) // column aka height
    {
        for (int j = 0; j < width; j++) // row aka width
        {
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            // computes red
            int sepiaRed = round ( ((float).393 * red) + ((float).769 * green) + ((float).189 * blue));
              if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            // computes green
            int sepiaGreen = round ( ((float) .349 * red) + ((float).686 * green) + ((float).168 * blue) );
                if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            // compute blue
            int sepiaBlue = round ( ((float).272 * red) + ((float) .534 * green) + ((float).131 * blue) );

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

void swap(RGBTRIPLE * pixel1, RGBTRIPLE * pixel2)
{

    RGBTRIPLE temp = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = temp;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
}

bool valid_pixel(int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}

RGBTRIPLE blurred(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int red, green, blue; red = green = blue = 0;
    int numValidPixel = 0;
    for (int change_i = -1; change_i <= 1; change_i++)
    {
        for (int change_j = -1; change_j <= 1; change_j++)
        {
            int new_i = i + change_i;
            int new_j = j + change_j;
            if (valid_pixel(new_i, new_j, height, width))
            {
                numValidPixel++;
                red += image[new_i][new_j].rgbtRed;
                green += image[new_i][new_j].rgbtGreen;
                blue += image[new_i][new_j].rgbtBlue;
            }
        }
    }
    RGBTRIPLE blurred;
    blurred.rgbtRed = round((float)red / numValidPixel);
    blurred.rgbtGreen = round((float)green / numValidPixel);
    blurred.rgbtBlue = round((float)blue / numValidPixel);
      return blurred;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = blurred(i, j, height, width, image);
        }
    }

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            image[i][j] = new_image[i][j];
}
