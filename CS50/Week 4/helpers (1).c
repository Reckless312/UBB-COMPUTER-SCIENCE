#include "helpers.h"
#include <math.h>
#include <stdbool.h>
int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
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

RGBTRIPLE calculate_edge(int height, int width, int i, int j, RGBTRIPLE image[height][width])
{
    double red_gx, green_gx, blue_gx, red_gy, green_gy, blue_gy;
    red_gx = green_gx = blue_gx = red_gy = green_gy = blue_gy = 0;
    for (int k = i - 1; k <= i + 1; k++)
    {
        for (int p = j - 1; p <= j + 1; p++)
        {
            if (valid_position(height, width, k, p))
            {
                red_gx += image[k][p].rgbtRed * gx[k - (i - 1)][p - (j - 1)];
                green_gx += image[k][p].rgbtGreen * gx[k - (i - 1)][p - (j - 1)];
                blue_gx += image[k][p].rgbtBlue * gx[k - (i - 1)][p - (j - 1)];
                red_gy += image[k][p].rgbtRed * gy[k - (i - 1)][p - (j - 1)];
                green_gy += image[k][p].rgbtGreen * gy[k - (i - 1)][p - (j - 1)];
                blue_gy += image[k][p].rgbtBlue * gy[k - (i - 1)][p - (j - 1)];
            }
        }
    }
    double red = sqrt(red_gx * red_gx + red_gy * red_gy);
    double green = sqrt(green_gx * green_gx + green_gy * green_gy);
    double blue = sqrt(blue_gx * blue_gx + blue_gy * blue_gy);
    get_closer(&red);
    get_closer(&green);
    get_closer(&blue);
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = calculate_edge(height, width, i, j, image);
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
