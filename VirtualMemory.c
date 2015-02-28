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


//	int i;
//	for(i = 0; i < 30; i++)
//	{
//		vAddr address1 = allocateNewInt();
//	}

	vAddr indexes[1000];
	int i ;
	for( i = 0; i < 500; i++)
	{
		indexes[i] = allocateNewInt();
		int *value = accessIntPtr(indexes[i]);
		*value = (i * 3);
		printf("Changing value at vAddr %d to %d\n", indexes[i], RAMArray[pageTable[indexes[i]].RAMIndex]);
		unlockMemory(indexes[i]);
	}
	for( i = 0; i < 500; i++)
	{
//		printf("Free memory at vAddr %d\n", indexes[i]);
		freeMemory(indexes[i]);
	}
}
