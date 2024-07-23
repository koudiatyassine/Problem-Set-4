#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Check for correct usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s image\n", argv[0]);
        return 1;
    }

    // Open input file
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    // Buffer to read blocks
    uint8_t buffer[BLOCK_SIZE];

    // Variables to track JPEG files
    FILE *output_file = NULL;
    char filename[8]; // "###.jpg\0"
    int file_count = 0;

    // Read from input file
    while (fread(buffer, BLOCK_SIZE, 1, input_file))
    {
        // Check if the current block is the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous output file if it exists
            if (output_file != NULL)
            {
                fclose(output_file);
            }

            // Create new JPEG file
            sprintf(filename, "%03d.jpg", file_count++);
            output_file = fopen(filename, "w");
            if (output_file == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                fclose(input_file);
                return 1;
            }

            // Write current block to the new JPEG file
            fwrite(buffer, BLOCK_SIZE, 1, output_file);
        }
        else
        {
            // Continue writing to the current JPEG file if one is open
            if (output_file != NULL)
            {
                fwrite(buffer, BLOCK_SIZE, 1, output_file);
            }
        }
    }

    // Close input and output files
    fclose(input_file);
    if (output_file != NULL)
    {
        fclose(output_file);
    }

    return 0;
}
