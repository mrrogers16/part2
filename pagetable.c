#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 128
#define OFFSET_BITS 7
#define PAGE_BITS 5

struct PageTableEntry
{
    int frame_number;
    int isValid;
    int lru_counter;
};

void initPageTableEntry(struct PageTableEntry *entry, int frame)
{
    entry->frame_number = frame;
    entry->isValid = 1;
    entry->lru_counter = 0;
}

unsigned long translateVirtualToPhysical(struct PageTableEntry *page_table, unsigned long virtual_addr)
{
    int page_num = virtual_addr >> OFFSET_BITS;

    if (page_table[page_num].isValid)
    {
        int frame_number
    }
}