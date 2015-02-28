/* UserAPI.c - defines user functions for accessing memory */

#include "hierarchy.h"
#include "UserAPI.h"
#include "pageTable.h"
#include <stdio.h>//for printf
#include <stdlib.h>

// helper function wich ckecks to see if a given array in memory is full
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
			exit(1);
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
			exit(1);
			break;
	}
}

// takes an array of physical memory and returns the index of the first empty page in that frame
int findEmptyFrame(MemoryLocation loc)
{
	int memcap;		// number of frames in this layer of physical memory
	int i;

	switch (loc) {
       		 case RAM:
			memcap = 25;
			for (i = 0; i < memcap; i++) {
				if (RAMArray[i] == -1)
				return i;
			}
			break;
		case SSD:
			memcap = 100;
			for (i = 0; i < memcap; i++) {
				if (SSDArray[i] == -1)
				return i;
			}
			break;
		case HD:
			memcap = 1000;
			for (i = 0; i < memcap; i++) {
				if (HDArray[i] == -1)
					return i;
			}
			break;

		default:
			errorWithContext("Invalid input: Not a MemoryLocation!");
			break;
	}

	// return -1 if we don't find an empty frame
	return -1;
}

/* evicts a page from either the SSD or RAM, given by the input location. This function returns the index of the given
 * array which has been changed. Ex: if a page must be evicted from RAMArray, location is RAM, and the return is a RAMIndex. */
int evictPageFrom(MemoryLocation location)
{
	// return error if all pages in array we are evicting from are locked
	if (isArrayLocked(location)) {
		printf("Sorry, all pages locked.\n");
		return -1;
	}

	int memcap;			// number of pages that this memory layer can hold
	int evictIndex;		// index of the page to be evicted

	if (location == RAM)
		memcap = 25;
	else if (location == SSD)
		memcap = 100;

	// evict a page at random
	evictIndex = rand() % memcap;

	// make sure the page we find isn't locked
	vAddr pt_entry;		// the page table address of the page to be evicted

	printf("   about to call pageTableIndex\n");
	pt_entry = pageTableIndex(evictIndex, location);

	// if the page is locked, rummage through pages until we find one that isn't
	while (pageTable[pt_entry].isLocked) {
		evictIndex = rand() % memcap;
		pt_entry = pageTableIndex(evictIndex, location);
	}

	printf("   Found a page to evict which is unlocked\n");

	// find an empty space in slower memory
	int destination;		// address of unallocated page frame

	//Make sure the most recently accessed value in the RAM or SSD is copied to lower pages
	if(location == RAM)
	{
		int currentMemVal = RAMArray[evictIndex];
		printf("previous memory value (eviction from RAM) is: %d \n", currentMemVal);

		//update the lower memory pages if necessary
		if(pageTable[pt_entry].SSDIndex != -1){
			RAMArray[evictIndex] = -1;
			SSDArray[pageTable[pt_entry].SSDIndex] = currentMemVal;
			printf("   copying page from RAM into SSD\n");
		}
		if(pageTable[pt_entry].HDIndex != -1){
			RAMArray[evictIndex] = -1;
			HDArray[pageTable[pt_entry].HDIndex] = currentMemVal;
			printf("   copying page from RAM into HD\n");
		}

		//check to see if the page is already in SSD. If already there, return
		if(pageTable[pt_entry].SSDIndex != -1)
			return evictIndex;
	}
	else if(location == SSD)
	{
		int currentMemVal = SSDArray[evictIndex];
		printf("previous memory value (eviction from SSD) is: %d \n", currentMemVal);

		if(pageTable[pt_entry].HDIndex != -1){
			SSDArray[evictIndex] = -1;
			HDArray[pageTable[pt_entry].HDIndex] = currentMemVal;
			printf("   copying page from SSD into HD. Value is %d \n", currentMemVal);
			return evictIndex;
		}

	}

	if (location == RAM) {
		if (isArrayFull(SSD)){			// if SSD is full, perform a cascading eviction
			printf("   evicting from RAM and SSD is full\n");
			destination = evictPageFrom(SSD);
			printf("   successfully evicted a page from SSD \n");
			if(destination == -1){
				errorWithContext("   Unable to evict a page from SSD");
				exit(1);
			}
		}
		else							// otherwise just find an empty spot
			destination = findEmptyFrame(SSD);
	}
	else if (location == SSD){
		printf("   evicting from SSD and finding an empty space in HD\n");
		destination = findEmptyFrame(HD);
		}

	// assign value of evicted page to empty space
	if (location == RAM) {
		printf("   Moving page from RAM into SSD\n");
		SSDArray[destination] = RAMArray[evictIndex];
		// remove value from location in memory
		RAMArray[evictIndex] = -1;
		// update page table data
		pageTable[pt_entry].RAMIndex = -1;
		pageTable[pt_entry].SSDIndex = destination;
		pageTable[pt_entry].location = SSD;
	}

	if (location == SSD) {
		printf("   Moving page from SSD into HD\n");
		HDArray[destination] = SSDArray[evictIndex];
		// remove value from location in memory
		SSDArray[evictIndex] = -1;
		// update page table data
		pageTable[pt_entry].SSDIndex = -1;
		pageTable[pt_entry].HDIndex = destination;
		pageTable[pt_entry].location = HD;
	}

	printf("   returning final value of %d\n", evictIndex);
	return evictIndex;

}

/* Reserves a new memory location of size int in RAM. Return -1 if no memory available */
vAddr allocateNewInt()
{
	//simple algorithm which determines whether or not there is an empty space in the RAM

	// Find out how many pages exist in RAM or SSD
	int pagesInRAM = 0;
	int pagesInSSD = 0;
	int pagesInHD = 0;

	// If this flag is still 0 when we get to the end of the page table,
	// the table's full!
	int notAllAllocated = 0;

	int i;
	for(i = 0; i < 1000; i++)
	{
		if(pageTable[i].isAllocated){
			//instead of returning the index of the array, instead use that index to find
			//the corresponding vAddr in the page table
			if (pageTable[i].RAMIndex != -1) {
				pagesInRAM++;
//				printf("Page at Addr %d is in RAM    Page is in RAMIndex %d\n", i, pageTable[i].RAMIndex);
				}
			if (pageTable[i].SSDIndex != -1){
				pagesInSSD++;
//				printf("Page at Addr %d is in SSD    Page is in SSDIndex %d\n", i, pageTable[i].SSDIndex);
				}
			if(pageTable[i].HDIndex != -1){
				pagesInHD++;
//				printf("Page at Addr %d is in HD    Page is in SSDIndex %d\n", i, pageTable[i].HDIndex);

				}
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

	printf("pagesInRAM: %d   pagesInSSD: %d   pagesInHD: %d\n", pagesInRAM, pagesInSSD, pagesInHD);

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
			if(evictPageFrom(SSD) == -1){
				errorWithContext("Not able to evict a page from SSD");
				return -1;
			}

		}
		// evict a page from RAM to make room, return the newly opened index in RAM
		indexInRAM = evictPageFrom(RAM);

		if(indexInRAM == -1){
			errorWithContext("Not able to evict a page from SSD");
			return -1;
		}

		printf("Evicted a page from RAM at index %d", indexInRAM);

		vAddr k;
		for(k = 0; k < 1000; k++)
		{
			if(!pageTable[k].isAllocated)
			{
				pageTable[k].isAllocated = 1;
				pageTable[k].RAMIndex = indexInRAM;
				pageTable[k].location = RAM;

				printf("Moved a page into RAM at index %d\n", pageTable[k].RAMIndex);

				RAMArray[indexInRAM] = 0;
				printf("vAddr is: %d\n", k);
				return k;

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
					if(RAMArray[j] == -1)
						break;
				}

				pageTable[i].isAllocated = 1;
				pageTable[i].RAMIndex = j;
				printf("RAMIndex for page %d is changed to %d", i, j);
				RAMArray[j] = 0;
				pageTable[i].location = RAM;

//				printf("Successfully reached end\nReturn is: %d\n\n", i);

				return i;

			}

		}


	}

	//is this necessary anymore?
	errorWithContext("No available locations in RAM");
	return -1; //no available locations in RAM

}

/* Obtains the indicated memory page from lower levels of hierarchy if needed. Returns an int pointer
 * to the location in RAM. The page is locked in memory and is immediately considered "dirty". Return
 * NULL if the pointer cannot be provided (ex: page must be brought to RAM but all of RAM is locked) */
int *accessIntPtr(vAddr address)
{
	pageStruct *structOfInterest = &pageTable[address];

	if(!structOfInterest->isAllocated){
		errorWithContext("You tried to access a value which has not been previously allocated");
		exit(0);
	}

	printf("Checking where the page is stored\n");
	//if the page is already in RAM, return a pointer to the necessary memory in RAM
	if(structOfInterest->location == RAM)
	{
		printf("Page is in RAM\n");
		structOfInterest->isDirty = 1;
		structOfInterest->isLocked = 1;
		return &RAMArray[structOfInterest->RAMIndex];
	}
	//if the page is not in RAM but is currently in SSD, evict a page from SSD
	else if(structOfInterest->location == SSD)
	{
		printf("page is in SSD\n");
		int newlyOpenedIndexInRAM = evictPageFrom(RAM);

		if(newlyOpenedIndexInRAM == -1){
			printf("error during evictPageFrom\n");
			errorWithContext("Not able to evict a page from RAM");
			return NULL;
		}

		RAMArray[newlyOpenedIndexInRAM] = 0;

		structOfInterest->RAMIndex = newlyOpenedIndexInRAM;
		structOfInterest->isDirty = 1;
		structOfInterest->isLocked = 1;

		return &RAMArray[structOfInterest->RAMIndex];

	}
	//page is in HD. evict page from SSD and then from RAM
	else if(structOfInterest->location == HD)
	{
		printf("Page is in HD\n");
		int memVal = HDArray[structOfInterest->HDIndex];
		int newlyOpenedIndexInRAM;
		int newlyOpenedIndexInSSD;

		printf("Data stored in HDArray[%d] is %d \n", structOfInterest->HDIndex, memVal);

		newlyOpenedIndexInSSD = evictPageFrom(SSD);

		if(newlyOpenedIndexInSSD == -1){
			errorWithContext("Not able to evict a page from SSD");
			return NULL;
		}

		structOfInterest->SSDIndex = newlyOpenedIndexInSSD;
		SSDArray[newlyOpenedIndexInSSD] = memVal;

		printf("Changes SSDArray [%d] to %d\n", newlyOpenedIndexInSSD, memVal);

		printf("about to evict page from RAM\n");
		newlyOpenedIndexInRAM = evictPageFrom(RAM);

		printf("Successfully evicted a page from RAM\n");

		if(newlyOpenedIndexInRAM == -1){
//			printPageTableData();
			errorWithContext("Not able to evict a page from RAM");
			return NULL;
		}

		RAMArray[newlyOpenedIndexInRAM] = memVal;

		printf("Changes RAMArray[%d] to %d\n", newlyOpenedIndexInRAM, memVal);

		printf("Saved value in RAM to be %d\n", memVal);

		structOfInterest->RAMIndex = newlyOpenedIndexInRAM;
		structOfInterest->isDirty = 1;
		structOfInterest->isLocked = 1;

		printf("Returning ptr to RAM\n");
		return &RAMArray[structOfInterest->RAMIndex];
	}

	//If you have gotten here, something has gone wrong
	errorWithContext("Reached end of AccessIntPtr without return");
	exit(1);
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
