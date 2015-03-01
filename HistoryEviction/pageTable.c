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
	printf("isLocked: %d isAllocated: %d isDirty: %d ", page.isLocked, page.isAllocated, page.isDirty);
	switch(page.location){
		case NONE:
			printf("level: NONE ");
			break;
		case SSD:
			printf("level: SSD ");
			break;
		case RAM:
			printf("level: RAM ");
			break;
		case HD:
			printf("level: HD ");
			break;
		default:
			printf("level: UNKNOWN ");
			break;
	}
	printf("RAMIndex: %d SSDIndex: %d HDIndex: %d lastAccessed: %ld \n", page.RAMIndex, page.SSDIndex, page.HDIndex, page.lastAccessed);
}

//	pass in a page's location in physical memory and return its address in the page table
vAddr pageTableIndex(int arrayIndex, MemoryLocation loc)
{
	vAddr i;
	for (i = 0; i < 1000; i++) {
		if (loc == RAM && pageTable[i].RAMIndex == arrayIndex)
			return i;
		if (loc == SSD && pageTable[i].SSDIndex == arrayIndex)
			return i;
		if (loc == HD && pageTable[i].HDIndex == arrayIndex)
			return i;
	}
}

void printPageTableData()
{
	vAddr address;
	for(address = 0; address < 50; address++)
	{
		printf("vAddr: %d ", address);
		printPageData(pageTable[address]);
	}


}
