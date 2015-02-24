/* UserAPI.c - defines user functions for accessing memory */

#include "hierarchy.h"
#include "UserAPI.h"
#include <stdlib.h>//for printf

/* Reserves a new memory location of size int in RAM. Return -1 if no memory available */
vAddr allocateNewInt()
{

	int i;
	for(i = 0; i < 25; i++)
	{
		if(RAMArray[i] == -1)
			return i;
	}
	//if we have reached this point, we need to evict a page currently in RAMArray
	return -1; //no available locations in RAM

}

/* Obtains the indicated memory page from lower levels of heirarchy if needed. Returns an int pointer
 * to the location in RAM. The page is locked in memory and is immediately considered "dirty". Return
 * NULL if the pointer cannot be prvided (ex: page must be brought to RAM but all of RAM is locked) */
int *accessIntPtr(vAddr address)
{


}

/* Unlocks the memory, allowing it to be swapped out to disk if needed. This command makes all previous
 * pointers invalid and must not be used */
void unlockMemory(vAddr address)
{


}

/* Frees the memory and deletes any swapped out copies of the page */
void freeMemory(vAddr address)
{

}
