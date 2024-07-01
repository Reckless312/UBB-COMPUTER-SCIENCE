#include "helpers.h"
#include <math.h>
#include <stdbool.h>

void get_closer(double *value)
{
    if (*value > 255)
    {
        *value = 255;
        return;
    }
    return;
}
bool valid_position(int height, int width, int k, int p)
{
    if (k < 0 || k >= height)
    {
        return false;
    }
    if (p < 0 || p >= width)
    {
        return false;
    }
    return true;
}

RGBTRIPLE calculate_blur(int height, int width, int i, int j, RGBTRIPLE image[height][width])
{
    double red, green, blue;
    int valid_count = 0;
    red = green = blue = 0;
    for (int k = i - 1; k <= i + 1; k++)
    {
        for (int p = j - 1; p <= j + 1; p++)
        {
            if (valid_position(height, width, k, p))
            {
                red += image[k][p].rgbtRed;
                green += image[k][p].rgbtGreen;
                blue += image[k][p].rgbtBlue;
                valid_count++;
            }
        }
    }
    red = red / (double) valid_count;
    green = green / (double) valid_count;
    blue = blue / (double) valid_count;
    RGBTRIPLE result;
    result.rgbtRed = (int) round(red);
    result.rgbtGreen = (int) round(green);
    result.rgbtBlue = (int) round(blue);
    return result;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double average =
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue =
                (int) round(average);
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
            double sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                              .189 * image[i][j].rgbtBlue;
            double sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                .168 * image[i][j].rgbtBlue;
            double sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                               .131 * image[i][j].rgbtBlue;
            get_closer(&sepiaRed);
            get_closer(&sepiaGreen);
            get_closer(&sepiaBlue);
            image[i][j].rgbtRed = (int) round(sepiaRed);
            image[i][j].rgbtGreen = (int) round(sepiaGreen);
            image[i][j].rgbtBlue = (int) round(sepiaBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int middle = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < middle; j++)
        {
            RGBTRIPLE aux = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = aux;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = calculate_blur(height, width, i, j, image);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}
