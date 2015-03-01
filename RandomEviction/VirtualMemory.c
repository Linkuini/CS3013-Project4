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

void memoryMaxer()		// allocates all pages, assigns them a value, unlocks, and then frees them
{
	vAddr indexes[1000];
	for (int i = 0; i < 1000; ++i) {
		indexes[i] = allocateNewInt();
		int *value = accessIntPtr(indexes[i]);
		*value = (i * 3);
		unlockMemory(indexes[i]);
	}
	for (int i = 0; i < 1000; ++i) {
		freeMemory(indexes[i]);
	}
}

void memoryOverload()	// allocate memory until capacity is exceeded
{
	vAddr indexes[1000];
	for (int i = 0; i < 1001; ++i) {
		indexes[i] = allocateNewInt();
		int *value = accessIntPtr(indexes[i]);
		*value = (i * 3);
		unlockMemory(indexes[i]);
	}
	for (int i = 0; i < 1000; ++i) {
		freeMemory(indexes[i]);
	}
}

void tryLock()		// attempt to evict a locked page from RAM
{
	vAddr indexes[1000];
	for (int i = 0; i < 130; ++i) {
		indexes[i] = allocateNewInt();
		int *value = accessIntPtr(indexes[i]);
		*value = (i * 3);
	}
	for (int i = 0; i < 130; ++i) {
		indexes[i+130] = allocateNewInt();
	}
}

void accessNothing()		// attempt to access a page that has not been allocated
{
	vAddr indexes[1000];
	for (int i = 0; i < 130; ++i) {
		int *value = accessIntPtr(indexes[i]);
		*value = (i * 3);
		unlockMemory(indexes[i]);
	}
	for (int i = 0; i < 130; ++i) {
		freeMemory(indexes[i]);
	}
}

void accessTwice()		// attempt to access the same page twice
{
	vAddr indexes[1000];
	for (int i = 0; i < 130; ++i) {
		indexes[i] = allocateNewInt();
		int *value = accessIntPtr(indexes[i]);
		*value = (i * 3);
		*value = accessIntPtr(indexes[i]);
		*value = (i * 3);
		unlockMemory(indexes[i]);
	}
	for (int i = 0; i < 130; ++i) {
		freeMemory(indexes[i]);
	}
}

void mainTest()		// we used this to test general functionality during development
{
	vAddr indexes[1000];
	int i;
	for(i = 0; i < 130; i++)
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
	
	int k;
	for(k = 0; k < 500; k++)
	{
		printf("Attempting to access and change vAddr %d\n", k);
		
		int *value = accessIntPtr(indexes[k]);
		//printf("isArrayFull(RAM) is: %d", isArrayFull(RAM));
		if(value == NULL){
			errorWithContext("Unable to access the desired memory");
			exit(1);
		}
		*value = (*value * 5);
		//printf("value is: %d\n", *value);
		printf("Re-Changing val at vAddr %d to %d\n", indexes[k], *value);
		if(RAMArray[pageTable[indexes[k]].RAMIndex] == -1){
			errorWithContext("The value we just changed is now -1");
			exit(1);
		}
		unlockMemory(indexes[k]);
	}
	//print the pageTable before freeing all the memory
	printPageTableData();
	
	for(i = 0; i < 130; i++)
	{
		//	printf("Free memory at vAddr %d\n", indexes[i]);
		freeMemory(indexes[i]);
	}
}

int main(int argc, char* argv[]){
	srand(time(NULL));

	//initialize the memory and set up for use
	initHierarchy();
	initPageTable();

	vAddr indexes[1000];
	int i;
	for(i = 0; i < 130; i++)
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

	int k;
	for(k = 0; k < 500; k++)
	{
		printf("Attempting to access and change vAddr %d\n", k);

		int *value = accessIntPtr(indexes[k]);
		//printf("isArrayFull(RAM) is: %d", isArrayFull(RAM));
		if(value == NULL){
			errorWithContext("Unable to access the desired memory");
			exit(1);
		}
		*value = (*value * 5);
		//printf("value is: %d\n", *value);
		printf("Re-Changing val at vAddr %d to %d\n", indexes[k], *value);
		if(RAMArray[pageTable[indexes[k]].RAMIndex] == -1){
			errorWithContext("The value we just changed is now -1");
			exit(1);
		}
		unlockMemory(indexes[k]);
	}
	//print the pageTable before freeing all the memory
	printPageTableData();

	for(i = 0; i < 130; i++)
	{
	//	printf("Free memory at vAddr %d\n", indexes[i]);
		freeMemory(indexes[i]);
	}

}
