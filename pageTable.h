/* handles the definition of a page struct and holds the page table itself */

#include "hierarchy.h"

//Enum to represent where the page is currently located
typedef enum
{
	RAM,
	SSD,
	HD,
	NONE
} MemoryLocation;

typedef struct pageStruct{
	int isLocked; //0 if unlocked, 1 if locked
	int isAllocated; //0 if unallocated, 1 if allocated
	int isDirty; //0 if clean, 1 if dirty
	MemoryLocation location; //where the page is currently stored
	vAddr memoryIndex; //-1 if unallocated?
	long lastAccessed; //time of last access
} pageStruct;

pageStruct pageTable[1000];

void initPageStruct(pageStruct page);

void initPageTable(pageStruct table[]);
