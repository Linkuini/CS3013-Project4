#ifndef _USER_API_H
#define _USER_API_H


vAddr allocateNewInt();

int *accessIntPtr(vAddr address);

void unlockMemory(vAddr address);

void freeMemory(vAddr address);


#endif _USER_API_H
