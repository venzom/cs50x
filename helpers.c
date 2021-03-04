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
    
    // Loop through each pixel in image
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate each new R, G r B value sepia color with provided formula
            r = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            g = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            b = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            
            // Check value for each color is greater than 255(max), if so make it 255
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
            
            // Round number and add replace in image
            image[i][j].rgbtRed = round(r);
            image[i][j].rgbtGreen = round(g);
            image[i][j].rgbtBlue = round(b);
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
    // Create a duplicate of the image to take values from it to add to current image
    RGBTRIPLE dupl[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            dupl[i][j] = image[i][j];
        }
    }
    
    // Loop through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float r = 0, g = 0, b = 0;
            
            // Loop through each surrounding pixel
            // If surrounding pixel is outside the image, ignore
            // If surrounding pixel is inside image, add to sum of each color(r, g, b)
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixels are outside image, top and bottom
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    
                    // Check if pixels are outside the image, left and right. 
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    
                    // Tally the pizels that will be added
                    count++;
                    
                    // Add up the pixels
                    r += dupl[i + k][j + l].rgbtRed;
                    g += dupl[i + k][j + l].rgbtGreen; 
                    b += dupl[i + k][j + l].rgbtBlue;
                }
            }
            
            // Take the average of surrounding pixels and replace it in "image"
            image[i][j].rgbtRed = round(r / count);
            image[i][j].rgbtGreen = round(g / count);
            image[i][j].rgbtBlue = round(b / count);
        }
    }
    return;
}
