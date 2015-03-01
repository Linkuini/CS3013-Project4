#ifndef _HIERARCHY_H
#define _HIERARCHY_H

#include <sys/time.h>
#include "Error.h"

int RAMArray[25];
int SSDArray[100];
int HDArray[1000];

typedef signed short vAddr;

void initHierarchy();

#endif
