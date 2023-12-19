#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double average = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = 0;
            average += image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen;
            average /= 3.0;
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    double sred = 0, sgreen = 0, sblue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sred = 0, sgreen = 0, sblue = 0;
            sred = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            sgreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            sblue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            if (sred > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(sred);
            }

            if (sgreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(sgreen);
            }

            if (sblue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(sblue);
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (width % 2 != 0)
            {
                if (j >= round(width / 2))
                {
                    break;
                }
                else
                {
                    RGBTRIPLE temp[height][width];
                    temp[i][j] = image[i][j];
                    image[i][j] = image[i][width - (j + 1)];
                    image[i][width - (j + 1)] = temp[i][j];
                }
            }
            else
            {
                if (j >= width / 2)
                {
                    break;
                }
                else
                {
                    RGBTRIPLE temp[height][width];
                    temp[i][j] = image[i][j];
                    image[i][j] = image[i][width - (j + 1)];
                    image[i][width - (j + 1)] = temp[i][j];
                }
            }
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    double tred = 0, tgreen = 0, tblue = 0;
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tred = 0, tgreen = 0, tblue = 0;
            if ((i == 0 && j == 0) || (i == height - 1 && j == 0) || (i == height - 1 && j == width - 1) ||
                (i == 0 && j == width - 1))
            {
                if (i == 0 && j == 0)
                {
                    tred += copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed;
                    tgreen +=
                        copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                    tblue += copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                }
                else if (i == height - 1 && j == 0)
                {
                    tred += copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed;
                    tgreen +=
                        copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen;
                    tblue += copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue;
                }
                else if (i == height - 1 && j == width - 1)
                {
                    tred += copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed;
                    tgreen +=
                        copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen;
                    tblue += copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue;
                }
                else if (i == 0 && j == width - 1)
                {
                    tred += copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed;
                    tgreen +=
                        copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen;
                    tblue += copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue;
                }
                tred /= 4.0;
                tgreen /= 4.0;
                tblue /= 4.0;
                image[i][j].rgbtRed = round(tred);
                image[i][j].rgbtGreen = round(tgreen);
                image[i][j].rgbtBlue = round(tblue);
            }
            else if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
            {
                if (i == 0)
                {
                    tred += copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                            copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed;
                    tgreen += copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                              copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                    tblue += copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                             copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                }
                else if (j == 0)
                {
                    tred += copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                            copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed;
                    tgreen += copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j].rgbtGreen +
                              copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                    tblue += copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                             copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                }
                else if (i == height - 1)
                {
                    tred += copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                            copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed;
                    tgreen += copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                              copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen;
                    tblue += copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                             copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue;
                }
                else if (j == width - 1)
                {
                    tred += copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                            copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed;
                    tgreen += copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                              copy[i][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen;
                    tblue += copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                             copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue;
                }
                tred /= 6.0;
                tgreen /= 6.0;
                tblue /= 6.0;
                image[i][j].rgbtRed = round(tred);
                image[i][j].rgbtGreen = round(tgreen);
                image[i][j].rgbtBlue = round(tblue);
            }
            else
            {
                tred += copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                        copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                        copy[i + 1][j + 1].rgbtRed;
                tgreen += copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                          copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                          copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                tblue += copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                         copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                         copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                tred /= 9.0;
                tgreen /= 9.0;
                tblue /= 9.0;
                image[i][j].rgbtRed = round(tred);
                image[i][j].rgbtGreen = round(tgreen);
                image[i][j].rgbtBlue = round(tblue);
            }
        }
    }
}

// swap
void swap(RGBTRIPLE a, RGBTRIPLE b)
{
    RGBTRIPLE tmp = a;
    a = b;
    b = tmp;
}