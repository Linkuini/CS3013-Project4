#include "pageTable.h"
#include <stdio.h>

void initPageStruct(pageStruct *page)
{
	page->isLocked = 0; //unlocked
	page->isAllocated = 0; //unallocated
	page->isDirty = 0;//clean
	page->location = NONE;
	page->RAMIndex = -1;// not currently located in RAM
	page->SSDIndex = -1;// not currently located in SSD
	page->HDIndex = -1; // not currently located in HD
	page->lastAccessed = -1; //not yet accessed
}

void initPageTable()
{
	int i;
	for(i = 0; i < 1000; i++)
	{
//		printf("Initializing page #%d\n", i);
		initPageStruct(&pageTable[i]);
	}
}

void printPageData(pageStruct page)
{
	printf("   isLocked: %d\n   isAllocated: %d\n   isDirty: %d\n", page.isLocked, page.isAllocated, page.isDirty);
	switch(page.location){
		case NONE:
			printf("   memory level: NONE\n");
			break;
		case SSD:
			printf("   memory level: SSD\n");
			break;
		case RAM:
			printf("   memory level: RAM\n");
			break;
		case HD:
			printf("   memory level: HD\n");
			break;
		default:
			printf("   memory level: UNKNOWN");
			break;
	}
	printf("   RAMIndex: %d\n   SSDIndex: %d\n   HDIndex: %d\n   lastAccessed: %ld\n", page.RAMIndex, page.SSDIndex, page.HDIndex, page.lastAccessed);
}
