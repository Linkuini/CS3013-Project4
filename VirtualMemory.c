//
//  VirtualMemory.c
//
//
//
//

#include <stdio.h>
#include "hierarchy.h"
#include "UserAPI.h"

int main(int argc, char* argv[]){

	vAddr address1;
	vAddr address2;

	int i;
	for(i = 0; i < 24; i++)
	{
		RAMArray[i] = i;
		printf("RAMArray[%d] = %d\n", i, RAMArray[i]);
	}

	address1 = allocateNewInt();
	printf("address1 is: %d\n", address1);

	RAMArray[24] = 24;
	printf("RAMArray[24] = %d\n", RAMArray[24]);

	address2 = allocateNewInt();

	printf("address2 is: %d\n", address2);

	for(i = 0; i < 25; i++)
	{
		printf("RAMArray[%d] = %d\n", i, RAMArray[i]);
	}
}
