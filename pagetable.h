#ifndef PAGETABLE_H
#define PAGETABLE_H

extern int page_faults;

struct PageTableEntry
{
    int frame_number;
    int isValid;
    int lru_counter;
};

void initPageTableEntry(struct PageTableEntry *entry, int frame);
void initPageTable(struct PageTableEntry *page_table, int tableSize);
int handlePageFault(struct PageTableEntry *page_table, int tableSize);
unsigned long translateVirtualToPhysical(struct PageTableEntry *page_table, unsigned long virtual_addr, int* freeFrame, int* referenceCount, int* pageFaults, int tableSize);

#endif