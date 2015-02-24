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

	initHierarchy();

	int i;
	for(i = 0; i < 24; i++)
	{
		RAMArray[i] = i;
	}

	initPageTable(pageTable);

}
