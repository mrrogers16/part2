#include <stdio.h>
#include <stdlib.h>
#include "pagetable.h"
#include "phypages.h"

#define PAGE_SIZE 128
#define FRAME_SIZE 128
#define OFFSET_BITS 7
#define PAGE_BITS 5
#define PHYSICAL_MEMORY 1024
#define VIRTUAL_MEMORY 4096
#define TOTAL_FRAMES (PHYSICAL_MEMORY / PAGE_SIZE)
#define PAGE_TABLE_SIZE (VIRTUAL_MEMORY / PAGE_SIZE)

int page_faults = 0;

FILE *open_file_rb(char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        fprintf(stderr, "Error opening %s\n", filename);
        return NULL;
    }
    return file;
}

FILE *open_file_wb(char *filename)
{
    FILE *file = fopen(filename, "wb");

    if (file == NULL)
    {
        fprintf(stderr, "Error opening %s\n", filename);
        return NULL;
    }
    return file;
}

int main(int argc, char *argv[])
{
    int freeFrame = 1;
    int pageFaults = 0;
    unsigned long virtual_addr, physical_addr;
    int referenceCount = 0;
    FILE *input = open_file_rb(argv[1]);
    FILE *output = open_file_wb(argv[2]);

    if (initializeFrame(TOTAL_FRAMES) != 0)
    {
        fprintf(stderr, "Error initializing free frames list.");
        return -1;
    }

    struct PageTableEntry page_table[PAGE_TABLE_SIZE];
    initPageTable(page_table, PAGE_TABLE_SIZE);

    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./%s input_file output_file", argv[0]);
        return -1;
    }

    while (fread(&virtual_addr, sizeof(unsigned long), 1, input) == 1)
    {
        physical_addr = translateVirtualToPhysical(page_table, virtual_addr, &freeFrame, &referenceCount, &pageFaults, PAGE_TABLE_SIZE);

        printf("here it is %lx\n", physical_addr);

        fwrite(&physical_addr, sizeof(unsigned long), 1, output);
        // if(physical_addr == (unsigned long)(-1))
        // {
        //     handlePageFault(page_table, PAGE_TABLE_SIZE);
        //     page_faults++;
        //     physical_addr = translateVirtualToPhysical(page_table, virtual_addr);
        // }
        // if(physical_addr != (unsigned long)(-1))
        // {
        //     fwrite(&physical_addr, sizeof(unsigned long), 1, output);
        // }
    }

    printf("Page Faults: %u\n", pageFaults);

    fclose(input);
    fclose(output);

    return 0;
}