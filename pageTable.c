#include "pageTable.h"
#include <stdio.h>

void initPageStruct(pageStruct *page)
{
	page->isLocked = 0; //unlocked
	page->isAllocated = 0; //unallocated
	page->isDirty = 0;//clean
	page->location = NONE;
	page->memoryIndex = -1;// no location in memory
	page->lastAccessed = -1; //not yet accessed
}

void initPageTable(pageStruct table[])
{
	int i;
	for(i = 0; i < 1000; i++)
	{
//		printf("Initializing page #%d\n", i);
		initPageStruct(&table[i]);
	}
}

void printPageData(pageStruct page)
{
	printf("   isLocked: %d\n   isAllocated: %d\n   isDirty: %d\n", page.isLocked, page.isAllocated, page.isDirty);
	switch(page.location){
		case NONE:
			printf("   location: NONE\n");
			break;
		case SSD:
			printf("   location: SSD\n");
			break;
		case RAM:
			printf("   location: RAM\n");
			break;
		case HD:
			printf("   location: HD\n");
			break;
		default:
			printf("   location: UNKNOWN");
			break;
	}
	printf("   memoryIndex: %d\n   lastAccessed: %ld\n", page.memoryIndex, page.lastAccessed);
}
