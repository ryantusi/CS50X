#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    // opening the card
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");

    // If cannot open file, exit
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // declaring variables
    unsigned char buffer[512];
    int counter = 0;
    FILE *outptr = NULL;
    char *file_name = malloc(8 * sizeof(char));

    // reading and finding JPEGs
    while (fread(buffer, sizeof(char), 512, inptr))
    {
        // checking the start header of a JPEG in the card
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // closing file when found a new JPEG image
            if (counter > 0)
            {
                fclose(outptr);
            }

            // creating filename first
            sprintf(file_name, "%03i.jpg", counter);

            // opening the output file
            outptr = fopen(file_name, "w");

            // counting images
            counter++;
        }

        // if the output file opens, start writing
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(char), 512, outptr);
        }
    }

    // free memory and close file
    free(file_name);
    fclose(inptr);
    fclose(outptr);

    return 0;
}