#include hierarchy.h


//initializes the memory arrays
void initHierarchy()
{
	int i;
	//initialize RAM
	for(i = 0; i < 25; i++){
		RAMArray[i] = -1;
	}

	//initialize SSD
	for(i = 0; i < 100; i++){
		SSDArray[i] = -1;
	}

	//initialize HD
	for(i = 0; i < 1000; i++){
		HDArray[i] = -1;
	}

}
