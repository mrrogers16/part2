#include <stdio.h>
#include <stdlib.h>

int next_free_frame = 1;

int allocateFrame()
{
    if (next_free_frame > 0)
    {
        next_free_frame--;
        return 1;
    }
    return -1;
}

void deallocateFrame()
{
    next_free_frame++;
}