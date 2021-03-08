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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
    
    // Define SOBOL operators
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    
    // Loop through each pixel in duplicate image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float rx, gx, bx, ry, gy, by;  
            rx = gx = bx = ry = gy = by = 0;
            
            // Loop through each surrounding pixel
            // If surrounding pixel is outside the image, assign black to it
            // If inside the image, apply corresponding SOBOL opetator
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixels are outside the image, top and bottom
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    
                    // Check if pixels area outside the image, left and right
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    
                    // Calculate Gx and Yx for each color
                    rx += (dupl[i + k][j + l].rgbtRed * (Gx[k + 1][l + 1])); 
                    gx += (dupl[i + k][j + l].rgbtGreen * (Gx[k + 1][l + 1]));
                    bx += (dupl[i + k][j + l].rgbtBlue * (Gx[k + 1][l + 1]));
                    
                    ry += (dupl[i + k][j + l].rgbtRed * (Gy[k + 1][l + 1]));
                    gy += (dupl[i + k][j + l].rgbtGreen * (Gy[k + 1][l + 1]));
                    by += (dupl[i + k][j + l].rgbtBlue * (Gy[k + 1][l + 1]));
                }
            }
            
            // Calculate each color as the square root of each rx and ry
            int r, g, b;
            r = round(sqrt((rx * rx) + (ry * ry)));
            g = round(sqrt((gx * gx) + (gy * gy)));
            b = round(sqrt((bx * bx) + (by * by)));
            
            // Cap each color at 255
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
            image[i][j].rgbtRed = r;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtBlue = b;
        }
    }
    
    return;
}
