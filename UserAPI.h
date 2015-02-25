#ifndef _USER_API_H
#define _USER_API_H

#include "hierarchy.h"
#include "pageTable.h"

vAddr allocateNewInt();

int *accessIntPtr(vAddr address);

void unlockMemory(vAddr address);

void freeMemory(vAddr address);

int evictPageFrom(MemoryLocation location);

#endif
