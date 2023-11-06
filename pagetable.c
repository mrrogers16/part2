#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 128
#define OFFSET_BITS 7
#define PAGE_BITS 5

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
    entry->frame_number = frame;
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
    int oldestIndex = -1;
    // make it far far away
    int oldestCounter = INT_MAX;

    for (i = 0; i < tableSize; i++)
    {
        if (page_table[i].isValid && page_table[i].lru_counter < oldestCounter)
        {
            // Update the LRU counter
            oldestCounter = page_table[i].lru_counter;
            // Update the index of the
            oldestIndex = i;
        }
    }

    if (oldestIndex != -1)
    {
        // frame to release/free
        int released = page_table[oldestIndex].frame_number;
        // update pte for new page
        page_table[oldestIndex].isValid = 0;
        page_table[oldestIndex].lru_counter = 0;
    }
}

// Returns physical address if valid entry, else returns 0
unsigned long translateVirtualToPhysical(struct PageTableEntry *page_table, unsigned long virtual_addr)
{
    int page_num = virtual_addr >> OFFSET_BITS;

    if (page_table[page_num].isValid)
    {
        int offset = virtual_addr & ((1 << OFFSET_BITS) - 1);
        int frame_num = page_table[page_num].frame_number;
        return (frame_num << OFFSET_BITS) | offset;
    }
    else
    {
        int new_frame
    }
}