#include <stdio.h>
#include <stdlib.h>

int next_free_frame = 1;
int max_frame;

int initializeFrame(int total_frames)
{
    if(total_frames > 0)
    {
        max_frame = total_frames;
        return 0;
    }
    else
    {
        return -1;
    }
}

int allocateFrame()
{
    if(next_free_frame < max_frame)
    {
        return next_free_frame++;
    }
    else
    {
        return -1;
    }
}