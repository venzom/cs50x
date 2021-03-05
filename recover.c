#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 512
typedef uint8_t BYTE;
// void check(FILE card);

BYTE buffer[512];
char sBuffer[8];
int count = 000;

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

    // Read file in steps of 512 bytes at a time

    //char *name;

    


    while (fread(&buffer, sizeof(BYTE), 512, card) != 0)
    {
        
        // Check first 4 bytes of file
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
            && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            
            sprintf(sBuffer, "%003i.jpg", count);
            FILE *name = fopen(sBuffer, "w");
            // fwrite(&buffer, sizeof(BYTE), 512, name);
            fwrite(&buffer, sizeof(BYTE), 512, name);
            do 
            {    
                fread(&buffer, sizeof(BYTE), 512, card);
                fwrite(&buffer, sizeof(BYTE), 512, name);
            }   
            while (!((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) 
                && (buffer[3] >= 0xe0 && buffer[3] <= 0xef)));
            fseek(card, -512, SEEK_CUR);    
            fclose(name);
            //check(*card);
            count++;
        }

    }


    //free(buffer);
    fclose(card);
    return 0;
}

// void check(FILE card)
// {
//     sprintf(sBuffer, "%003i.jpg", count);
//     FILE *name = fopen(sBuffer, "w");
//     fwrite(&buffer, sizeof(BYTE), 512, name);
//     do 
//     {    
        
//         fwrite(&buffer, sizeof(BYTE), 512, name);
//     }   
//     while (!((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) 
//         && (buffer[3] >= 0xe0 && buffer[3] <= 0xef)));
//     fclose(name);
// }