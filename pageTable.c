#include "pageTable.h"

void initPageStruct(pageStruct page)
{
	page.isLocked = 0; //unlocked
	page.isAllocated = 0; //unallocated
	page.isDirty = 0;//clean
	page.location = NONE;
	page.memoryIndex = -1;// no location in memory
	page.lastAccessed = -1; //not yet accessed
}

void initPageTable(pageStruct table[])
{
	int i;
	for(i = 0; i < 1000; i++)
	{
		initPageStruct(table[i]);
	}
}