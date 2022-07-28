#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Check if a file is added
    if (argv[1] == NULL || argv[2] != NULL)
    {
        printf(".raw image file is requiered");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    //Check if the file could be opened
    if (!file)
    {
        printf("file could not be opened");
        return 1;
    }
    int BLOCK_SIZE = 512;
    BYTE buffer[512];
    int n = 0; //Number of jpgs
    FILE *newFile = NULL; //The new file is defined
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        //Check if a new image begins
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Generate image name
            char name[8];
            sprintf(name, "%03i.jpg", n);
            newFile = fopen(name, "w");
            n++;
        }
        if (newFile != NULL)
        {
            //Write image
            fwrite(buffer, 1, BLOCK_SIZE, newFile);
        }
    }
}