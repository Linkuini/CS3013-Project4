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


	int i;
	for(i = 0; i < 30; i++)
	{
		vAddr address1 = allocateNewInt();
	}
}
