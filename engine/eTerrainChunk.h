// ****************************************************************************
// eTerrainChunk.h
//
//
// ****************************************************************************

#ifndef __ETERRAINCHUNK_H__
#define __ETERRAINCHUNK_H__

#include "eAbstractObject.h"

class TerrainChunk : public AbstractObject
{
public:
	TerrainChunk();
	TerrainChunk(float height, float x);
	
	int RespondsTo(EMSG );
	
	float height;
	float x;
};

#endif
