// ****************************************************************************
// eDebug.cpp
//
//
// ****************************************************************************

#include "eDebug.h"
#include <stdio.h>

void debug(int level, const char* msg)
{
	int i = 0;
	for (i = 0; i < level; i++)
	{
		printf("\t");
	}
	printf("%s\n", msg);
}
