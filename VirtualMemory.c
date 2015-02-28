//
//  VirtualMemory.c
//
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hierarchy.h"
#include "UserAPI.h"
#include "pageTable.h"

int main(int argc, char* argv[]){
	srand(time(NULL));

	//initialize the memory and set up for use
	initHierarchy();
	initPageTable();

	vAddr indexes[1000];
	int i;
	for(i = 0; i < 500; i++)
	{
		indexes[i] = allocateNewInt();
		int *value = accessIntPtr(indexes[i]);
		if(value == NULL){
			errorWithContext("Unable to access the desired memory");
			exit(1);
		}
		*value = (i * 3);
		printf("Changing value at vAddr %d to %d\n", indexes[i], RAMArray[pageTable[indexes[i]].RAMIndex]);
		unlockMemory(indexes[i]);
	}

	//why isn't this code working?
	int k;
	for(k = 0; k < 2; k++)
	{
		printf("Attempting to access and change vAddr %d\n", k);

		int *value = accessIntPtr(indexes[k]);
		printf("isArrayFull(RAM) is: %d", isArrayFull(RAM));
		if(value == NULL){
			errorWithContext("Unable to access the desired memory");
			exit(1);
		}
		*value = (k * 5);
		printf("value is: %d\n", *value);
		printf("Re-Changing val at vAddr %d to %d\n", indexes[k], *value);
		if(RAMArray[pageTable[indexes[k]].RAMIndex] == -1){
			errorWithContext("The value we just changed is now -1");
			exit(1);
		}
		unlockMemory(indexes[k]);
	}

	for(i = 0; i < 500; i++)
	{
	//	printf("Free memory at vAddr %d\n", indexes[i]);
		freeMemory(indexes[i]);
	}

//	printPageTableData();
}
