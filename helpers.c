#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double r, g, b;
    //int avg;
    
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            // Read RGB data from each pixel
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;
            
            // Get average of each pixel by calculating RGB average
            double avg = (r + g + b) / 3.0;
            avg = (round(avg));
            
            // Give each RGB the same value of "avg"
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // float r, g, b;
    
    // for (int i = 0; i <= height; i++)
    // {
    //     for (int j = 0; j <= width; j++)
    //     {
    //         // Calculate each new R, G r B value sepia color
    //         r = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
    //         g = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
    //         b = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
    //         r = round(r);
    //         g = round(g);
    //         b = round(b);
            
    //         if (r < 255)
    //         {
    //             r = 255;
    //         }
    //         else if (g < 255)
    //         {
    //             g = 255;
    //         }
    //         else if (b < 255)
    //         {
    //             b = 255;
    //         }
            
    //         image[i][j].rgbtRed = r;
    //         image[i][j].rgbtGreen = g;
    //         image[i][j].rgbtBlue = b;
    //     }
    // }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int r[width], g[width], b[width];
    
    
    for (int i = 0; i <= height; i++)
    {
        int w = width;
        for (int j = 0; j < width; j++)
        {
            // Read RGB data from each pixel
            r[j] = image[i][j].rgbtRed;
            g[j] = image[i][j].rgbtGreen;
            b[j] = image[i][j].rgbtBlue;
            
            // Give each RGB the same value the opposite pixel
            //w--;
        }
        for (int k = 0; k < width; k++)
        {
            image[i][w].rgbtRed = r[k];
            image[i][w].rgbtGreen = g[k];
            image[i][w].rgbtBlue = b[k];
            w--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
