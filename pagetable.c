#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "phypages.h"

#define PAGE_SIZE 128
#define OFFSET_BITS 7
#define PAGE_BITS 5

int max_frame;

// PageTableEntry struct
struct PageTableEntry
{
    int frame_number;
    int isValid;
    int lru_counter;
};

// Initiate one page table entry
void initPageTableEntry(struct PageTableEntry *entry, int frame)
{
    //entry->frame_number = frame;
    entry->isValid = 0;
    entry->lru_counter = 0;
}

// Initiate the entire page table
// TODO calculate tableSize in main to be passed here
void initPageTable(struct PageTableEntry *page_table, int tableSize)
{
    int i;

    for (i = 0; i < tableSize; i++)
    {
        initPageTableEntry(&page_table[i], i);
    }
}

int handlePageFault(struct PageTableEntry *page_table, int tableSize)
{
    int i;
    // initially invalid index
    int oldestIndex = 0;
    // make it far far away
    //int oldestCounter = INT_MAX;
    int lowestRef = page_table[1].lru_counter;

    for (i = 0; i < tableSize; i++)
    {
        if (page_table[i].isValid)
        {
            // Update the index of the
            oldestIndex = i;
            lowestRef = page_table[i].lru_counter;

            break;
        }
    }
    
    printf("\nthis is the oldestIndex Value: %d\n", oldestIndex);
    for (i = oldestIndex; i < tableSize; i++)
    {
        if (page_table[i].isValid && page_table[i].lru_counter < lowestRef)
        {
            oldestIndex = i;
            lowestRef = page_table[i].lru_counter;
        }
    }

    page_table[oldestIndex].isValid = 0;

    return page_table[oldestIndex].frame_number;
}

// Returns physical address if valid entry, else returns 0
unsigned long translateVirtualToPhysical(struct PageTableEntry *page_table, unsigned long virtual_addr, int *freeFrame, int *referenceCount, int *pageFaults, int tableSize)
{
    int page_num = virtual_addr >> OFFSET_BITS;
    int offset = virtual_addr & ((1 << OFFSET_BITS) - 1);
    int frame_num;
    if (page_table[page_num].isValid)
    {
        page_table[page_num].lru_counter = *referenceCount;
        (*referenceCount)++;
        frame_num = page_table[page_num].frame_number;
        // return (frame_num << OFFSET_BITS) | offset;
    }
    else if (*freeFrame < 8)
    {
        frame_num = (*freeFrame);
        (*freeFrame)++;
        (*pageFaults)++;
        // Do freeframe for frame_num
    }
    else
    {
        frame_num = handlePageFault(page_table, tableSize);
        (*pageFaults)++;
    }
    page_table[page_num].isValid = 1;
    page_table[page_num].frame_number = frame_num;
    page_table[page_num].lru_counter = *referenceCount;
    (*referenceCount)++;
    return (frame_num << OFFSET_BITS) | offset;
}