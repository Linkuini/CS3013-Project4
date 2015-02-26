/* UserAPI.c - defines user functions for accessing memory */

#include "hierarchy.h"
#include "UserAPI.h"
#include "pageTable.h"
#include <stdio.h>//for printf
#include <stdlib.h>

// see if an array in memory is full
int isArrayFull(MemoryLocation loc)
{
	int i;
	int full = 1;
	switch (loc) {
		case RAM:
			for (i=0; i<25; i++) {
				if (RAMArray[i] == -1)
					full = 0;
			}
			break;
		case SSD:
			for (i=0; i<100; i++) {
				if (SSDArray[i] == -1)
					full = 0;
			}
			break;
		case HD:
			for (i=0; i<1000; i++) {
				if (HDArray[i] == -1)
					full = 0;
			}
			break;
			
	default:
			errorWithContext("Invalid input: Not a MemoryLocation!");
			break;
	}
	return full;
}

// see if entire array is locked
int isArrayLocked(MemoryLocation loc)
{
	int RAMLocked = 1;		// is 1 if all pages in RAM are locked
	int SSDLocked = 1;		// same for SSD
	int HDLocked = 1;		// same for HD
	
	int i;
	for (i = 0; i<1000; i++) {
		if (!pageTable[i].isLocked) {
			if (pageTable[i].RAMIndex != -1)
				RAMLocked = 0;
			if (pageTable[i].SSDIndex != -1)
				SSDLocked = 0;
			if (pageTable[i].HDIndex != -1)
				HDLocked = 0;
		}
	}
	switch (loc) {
		case RAM:
			return RAMLocked;
			break;
		case SSD:
			return SSDLocked;
			break;
		case HD:
			return HDLocked;
			break;
  default:
			errorWithContext("Invalid input: Not a MemoryLocation!");
			break;
	}
}

/* evicts a page from either the SSD or RAM, given by the input location. This function returns the index of the given
 * array which has been changed. Ex: if a page must be evicted from RAMArray, location is RAM, and the return is a RAMIndex. */
int evictPageFrom(MemoryLocation location)
{
	int memcap;			// number of pages that this memory layer can hold
	int evictIndex;		// index of the page to be evicted
	
	if (location == RAM)
		memcap = 25;
	else if (location == SSD)
		memcap = 100;
	
	// evict a page at random
	evictIndex = rand() % memcap;
	
	// assign value of evicted page to empty space in a slower memory layer
	
	
	// remove value from location in memory
	
	// update page table data
	
	return evictIndex;

}

/* Reserves a new memory location of size int in RAM. Return -1 if no memory available */
vAddr allocateNewInt()
{
	//simple algorithm which determines whether or not there is an empty space in the RAM

	// Find out how many pages exist in RAM or SSD
	int pagesInRAM = 0;
	int pagesInSSD = 0;

	// If this flag is still 0 when we get to the end of the page table,
	// the table's full!
	int notAllAllocated = 0;

	int i;
	for(i = 0; i < 1000; i++)
	{
		if(pageTable[i].isAllocated){
			//instead of returning the index of the array, instead use that index to find
			//the corresponding vAddr in the page table
			if (pageTable[i].RAMIndex != -1)
				pagesInRAM++;
			if (pageTable[i].SSDIndex != -1)
				pagesInSSD++;
		}
		else
			notAllAllocated = 1;	// page table is not full

		if (pagesInRAM > 25 )		// if RAM or SSD are more than full, crash.
		{
			errorWithContext("Your RAM is not that big...");
			exit(1);
		}
		if (pagesInSSD > 100)
		{
			errorWithContext("Your SSD a splode!");
			exit(1);
		}
	}

	printf("pagesInRAM: %d\n pagesInSSD: %d\n", pagesInRAM, pagesInSSD);

	// refuse to allocate more than 1000 pages
	if (notAllAllocated == 0)
	{
		printf("Page table's full.\n");
		return -1;
	}
	//if we have reached this point, we need to evict a page currently in RAMArray
	if (pagesInRAM == 25)
	{
		int indexInRAM;

		//if the RAM and SSD are both full, evict a page from the SSD and then evict from the RAM
		if(pagesInSSD == 100)
		{
			evictPageFrom(SSD);


		}
		// evict a page from RAM to make room, return the newly opened index in RAM
		indexInRAM = evictPageFrom(RAM);
		printf("Evicted a page from RAM at index %d", indexInRAM);

		vAddr i;
		for(i = 0; i < 1000; i++)
		{
			if(!pageTable[i].isAllocated)
			{
				pageTable[i].isAllocated = 1;
				pageTable[i].RAMIndex = indexInRAM;
				pageTable[i].location = RAM;

				RAMArray[indexInRAM] = 0;
				printf("Are you at the success point? \nvAddr is: %d\n", i);
				return i;

			}
		}
		errorWithContext("You shouldn't be here but there are not any free pages in the page table");

		// for now, just print to console and return error
		printf("No room in RAM!");
			return -1;
	}
	else if(pagesInRAM < 25)
	{
		//scan for an unallocated page in pageTable, allocate it, and return the vAddr
		vAddr i;
		for(i = 0; i < 1000; i++)
		{

			//printf("vAddr is: %d\n", i);
			if(!pageTable[i].isAllocated)
			{
				int j;
				for(j = 0; j < 25; j++)
				{
					if(RAMArray[j] != -1 && RAMArray[j] != 0)
						break;
				}

				pageTable[i].isAllocated = 1;
				pageTable[i].RAMIndex = j;
				RAMArray[j] = 0;
				pageTable[i].location = RAM;

				printf("Successfully reached end\nReturn is: %d\n\n", i);

				return i;

			}

		}


	}
	//move this into the evictPageFrom() function
	//method #1: least recently accessed
	   //Scan the page table for pages located in RAM that are unlocked, and check the page's
	   //lastAccessed variable to find the oldest page. Move that page to the SSD, and place the new
           //page in its place.

	   //if there are no pages in RAM that are unlocked, return -1 and an error

	   //Add the page from RAM to the SSD, evicting a page from SSD if necessary
	   //If there are no unlocked pages in SSD and a page must be added to SSD, return -1 and an error

	   //return the vAddr of the newly opened page

	//is this necessary anymore?
	errorWithContext("You got to the end");
	return -1; //no available locations in RAM

}

/* Obtains the indicated memory page from lower levels of hierarchy if needed. Returns an int pointer
 * to the location in RAM. The page is locked in memory and is immediately considered "dirty". Return
 * NULL if the pointer cannot be provided (ex: page must be brought to RAM but all of RAM is locked) */
int *accessIntPtr(vAddr address)
{
	pageStruct structOfInterest = pageTable[address];
	//if the page is already in RAM, return a pointer to the necessary memory in RAM
	if(structOfInterest.location == RAM)
	{
		structOfInterest.isDirty = 1;
		structOfInterest.isLocked = 1;
		return &RAMArray[structOfInterest.RAMIndex];
	}
	//if the page is not in RAM but is currently in SSD, evict a page from SSD
	else if(structOfInterest.location == SSD)
	{
		int newlyOpenedIndexInRAM = evictPageFrom(SSD);

		RAMArray[newlyOpenedIndexInRAM] = 0;

		structOfInterest.RAMIndex = newlyOpenedIndexInRAM;
		structOfInterest.isDirty = 1;
		structOfInterest.isLocked = 1;

		return &RAMArray[structOfInterest.RAMIndex];

	}
	//page is in HD. evict page from SSD and then from RAM
	else if(structOfInterest.location == HD)
	{
		int newlyOpenedIndexInRAM;

		evictPageFrom(HD);

		newlyOpenedIndexInRAM = evictPageFrom(SSD);

		RAMArray[newlyOpenedIndexInRAM] = 0;

		structOfInterest.RAMIndex = newlyOpenedIndexInRAM;
		structOfInterest.isDirty = 1;
		structOfInterest.isLocked = 1;

		return &RAMArray[structOfInterest.RAMIndex];
	}


	//use the data in the page struct to move the corresponding page into RAM if not already

	//return the address of the memory located in RAM

}

/* Unlocks the memory, allowing it to be swapped out to disk if needed. This command makes all previous
 * pointers invalid and must not be used */
void unlockMemory(vAddr address)
{
	//change the isLocked variable to unlocked (0)
	pageTable[address].isLocked = 0;

	//should we do anything here about updating the arrays to have the same value? due to dirty bit

}

/* Frees the memory and deletes any swapped out copies of the page */
void freeMemory(vAddr address)
{
	//create a pointer to the page to be changed
	pageStruct *page = &pageTable[address];

	//make sure the page's data is removed from the RAM, SSD, and HD
	if(page->RAMIndex!=-1)
		RAMArray[page->RAMIndex] = -1;
	if(page->SSDIndex!=-1)
		SSDArray[page->SSDIndex] = -1;
	if(page->HDIndex!=-1)
		HDArray[page->HDIndex] = -1;

	//reset the page to init
	initPageStruct(page);
}
