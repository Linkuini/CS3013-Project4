/* UserAPI.c - defines user functions for accessing memory */

#include "hierarchy.h"
#include "UserAPI.h"
#include "pageTable.h"
#include <stdio.h>//for printf
#include <stdlib.h> 

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
		if (pagesInSSD > 100 )		
		{
			errorWithContext("Your SSD a splode!");
			exit(1);
		}
	}

	// refuse to allocate more than 1000 pages
	if (notAllAllocated == 0)
	{
		printf("Page table's full.\n");
		return -1;
	}
	//if we have reached this point, we need to evict a page currently in RAMArray
	if (pagesInRAM == 25)
	{
		// evict a page from RAM to make room

		// for now, just print to console and return error
		printf("No room in RAM!");
		return -1;
	}
	//method #1: least recently accessed
	   //Scan the page table for pages located in RAM that are unlocked, and check the page's
	   //lastAccessed variable to find the oldest page. Move that page to the SSD, and place the new
           //page in its place.

	   //if there are no pages in RAM that are unlocked, return -1 and an error

	   //Add the page from RAM to the SSD, evicting a page from SSD if necessary
	   //If there are no unlocked pages in SSD and a page must be added to SSD, return -1 and an error

	   //return the vAddr of the newly opened page

	//is this necessary anymore?
	return -1; //no available locations in RAM

}

/* Obtains the indicated memory page from lower levels of hierarchy if needed. Returns an int pointer
 * to the location in RAM. The page is locked in memory and is immediately considered "dirty". Return
 * NULL if the pointer cannot be provided (ex: page must be brought to RAM but all of RAM is locked) */
int *accessIntPtr(vAddr address)
{
	//scan through the page table for the corresponding vAddr

	//use the data in the page struct to move the corresponding page into RAM if not already

	//return the address of the memory located in RAM

}

/* Unlocks the memory, allowing it to be swapped out to disk if needed. This command makes all previous
 * pointers invalid and must not be used */
void unlockMemory(vAddr address)
{
	//scan the page table for the corresponding page related to the given address

	//change the isLocked variable to unlocked (0)


}

/* Frees the memory and deletes any swapped out copies of the page */
void freeMemory(vAddr address)
{

}
