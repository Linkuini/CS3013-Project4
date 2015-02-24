/* handles the definition of a page struct and holds the page table itself */

#ifndef _HIERARCHY_H
#define _HIERARCHY_H

#include "hierarchy.h"

//Enum to represent where the page is currently located
typedef enum
{
	NONE,
	SSD,
	HD,
	RAM
} MemoryLocation;

typedef struct pageStruct{
	int isLocked; //0 if unlocked, 1 if locked
	int isAllocated; //0 if unallocated, 1 if allocated
	int isDirty; //0 if clean, 1 if dirty
	MemoryLocation location; //where the page is currently stored
	vAddr memoryIndex; //-1 if unallocated?
	long lastAccessed; //time of last access
} pageStruct;

 // pageTable - table which will hold all the pageStruct pages for reference.
 // The first 25 pages in the table will represent the RAM. The next 100 will represent
 // the SSD, and the rest will represent the HD. Pages will be moved around as needed.
pageStruct pageTable[1000];

void initPageStruct(pageStruct *page);

void initPageTable(pageStruct table[]);

void printPageData(pageStruct page);

#endif