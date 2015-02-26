//
//  VirtualMemory.c
//
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include "hierarchy.h"
#include "UserAPI.h"
#include "pageTable.h"

int main(int argc, char* argv[]){
	srand(time(NULL));

	initHierarchy();

	initPageTable();

}
