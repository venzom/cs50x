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
    double r, g, b;
    
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate each new R, G r B value sepia color
            r = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            g = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            b = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            r = round(r);
            g = round(g);
            b = round(b);
            
            if (r > 255)
            {
                r = 255;
            }
            if (g > 255)
            {
                g = 255;
            }
            if (b > 255)
            {
                b = 255;
            }
            
            image[i][j].rgbtRed = r;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtBlue = b;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int r[width], g[width], b[width];
    
    
    for (int i = 0; i <= height; i++)
    {
        int w = width - 1;
        
        for (int j = 0; j < width; j++)
        {
            // Read RGB data from each pixel
            r[j] = image[i][j].rgbtRed;
            g[j] = image[i][j].rgbtGreen;
            b[j] = image[i][j].rgbtBlue;
        }
        for (int k = 0; k < width; k++)
        {
            // Give each RGB the same value the opposite pixel in same row
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
    // Create a duplicate of the image
    RGBTRIPLE dupl[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            dupl[i][j] = image[i][j];
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float r = 0, g = 0, b = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixels are outside image
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    count++;
                    r += dupl[i + k][j + l].rgbtRed;
                    g += dupl[i + k][j + l].rgbtGreen; 
                    b += dupl[i + k][j + l].rgbtBlue;
                }
            }
            image[i][j].rgbtRed = round(r / count);
            image[i][j].rgbtGreen = round(g / count);
            image[i][j].rgbtBlue = round(b / count);
        }
        // for (int k = 0; k <= width; k++)
        // {
        //     image[i][k].rgbtRed = round(r[k] / count);
        //     image[i][k].rgbtGreen = round(g[k] / count);
        //     image[i][k].rgbtBlue = round(b[k] / count);
            
        //     r[k] = g[k] = b[k] = count = 0.0;
            
        // }
        
    }
    return;
}
