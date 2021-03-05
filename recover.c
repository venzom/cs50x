#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Create size of Byte
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for 1 command line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file and check if it is valid
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Define buffer for each byte
    BYTE buffer[512];
    char sBuffer[8];
    int count = 000;    

    // Read file 512 bytes at a time
    while (fread(&buffer, sizeof(BYTE), 512, card) != 0)
    {
        // Check if the first 4 bytes of match JPEG format
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
            && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            // Create new file name and open file
            sprintf(sBuffer, "%003i.jpg", count);
            FILE *name = fopen(sBuffer, "w");
            
            // Continue writing until next 4 JPEG bytes are identified 
            do 
            {    
                fwrite(&buffer, sizeof(BYTE), 512, name);
                fread(&buffer, sizeof(BYTE), 512, card);
                if (feof(card))
                {
                    break;
                }   
            }   
            while (!((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) 
                     && (buffer[3] >= 0xe0 && buffer[3] <= 0xef)));
            
            // Rewind 512 bytes to not skip images    
            fseek(card, -512, SEEK_CUR);    
            
            // Close outfile
            fclose(name);
            
            // Increase count for next file name
            count++;
        }
    }

    // Close infile
    fclose(card);
    return 0;
}
