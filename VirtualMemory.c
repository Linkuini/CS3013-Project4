//
//  VirtualMemory.c
//
//
//
//

#include <stdio.h>
#include "hierarchy.h"
#include "UserAPI.h"
#include "pageTable.h"

int main(int argc, char* argv[]){

	vAddr address1;
	vAddr address2;

	int i;
	//Initialize the RAMArray elements to NULL
	for(i = 0; i < 25; i++)
	{
		RAMArray[i] = -1;
	}

	for(i = 0; i < 24; i++)
	{
		RAMArray[i] = i;
	}

	initPageTable(pageTable);

	printPageData(pageTable[0]);

	pageTable[0].location = HD;

	printPageData(pageTable[0]);
}
