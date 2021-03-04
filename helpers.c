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
    int count = 1;
    double avgR, avgG, avgB;
    
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <=width; j++)
        {
            if (i == 0 && j == 0)
            {
                avgR = (image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed 
                + image[i+1][j+1].rgbtRed) / 4.0;
                
                avgG = (image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen 
                + image[i+1][j+1].rgbtGreen) / 4.0;
                
                avgB = (image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue 
                + image[i+1][j+1].rgbtBlue) / 4.0;
                
                image[i][j].rgbtRed = round(avgR);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtBlue = round(avgB);
                break;
            }
            if (i == 0 && j == width - 1)
            {
                avgR = (image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i+1][j-1].rgbtRed
                + image[i+1][j].rgbtRed) / 4.0;
                
                avgG = (image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i+1][j-1].rgbtGreen
                + image[i+1][j].rgbtGreen) / 4.0;
                
                avgB = (image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i+1][j-1].rgbtBlue
                + image[i+1][j].rgbtBlue) / 4.0;
                
                image[i][j].rgbtRed = round(avgR);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtBlue = round(avgB);
                break;
            }
            if (i == width - 1 && j == width - 1)
            {
                avgR = (image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i][j-1].rgbtRed
                + image[i][j].rgbtRed) / 4.0;
                
                avgG = (image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j-1].rgbtGreen
                + image[i][j].rgbtGreen) / 4.0;
                
                avgB = (image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j-1].rgbtBlue
                + image[i][j].rgbtBlue) / 4.0;
                
                image[i][j].rgbtRed = round(avgR);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtBlue = round(avgB);
                break;
            }
            if (i == width - 1 && j == 0)
            {
                avgR = (image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j].rgbtRed
                + image[i][j+1].rgbtRed) / 4.0;
                
                avgG = (image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j].rgbtGreen
                + image[i][j+1].rgbtGreen) / 4.0;
                
                avgB = (image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j].rgbtBlue
                + image[i][j+1].rgbtBlue) / 4.0;
                
                image[i][j].rgbtRed = round(avgR);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtBlue = round(avgB);
                break;
            }
            // if (i > 0 && j > 0 && i < height - 1 && j < width - 1)
            // {
            //     avgR = (image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed
            //     + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed
            //     + image[i+1][j-1].rgbtRed+ image[i+1][j].rgbtRed+ image[i+1][j+1].rgbtRed) / 9.0;
                
            //     avgG = (image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen
            //     + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen
            //     + image[i+1][j-1].rgbtGreen+ image[i+1][j].rgbtGreen+ image[i+1][j+1].rgbtGreen) / 9.0;
                
            //     avgB = (image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue
            //     + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue
            //     + image[i+1][j-1].rgbtBlue+ image[i+1][j].rgbtBlue+ image[i+1][j+1].rgbtBlue) / 9.0;
                
            //     image[i][j].rgbtRed = round(avgR);
            //     image[i][j].rgbtGreen = round(avgG);
            //     image[i][j].rgbtBlue = round(avgB);
            // }
            
        }
    }
    return;
}
