// ****************************************************************************
// eTerrainChunk.cpp
//
//
// ****************************************************************************

#include "eTerrainChunk.h"

// ------------------------------------
TerrainChunk::TerrainChunk() : 
// ------------------------------------
	height(0),
	x(0)
{
	Box b = Box(Vector2(0, -100), Vector2(10, 100));
	GeomAttr* g = new GeomAttr(b);
	AddAttribute(g);

	AddComponent(ECOMP_RENDER);
	AddComponent(ECOMP_COLLISION);
}

// ------------------------------------
TerrainChunk::TerrainChunk(float height, float x) : 
// ------------------------------------
	height(height),
	x(x)
{
	Box b = Box(Vector2(0, -100), Vector2(10, 100 + height));
	GeomAttr* g = new GeomAttr(b);
	AddAttribute(g);
	AddAttribute(new SpatialAttr(x, 0));
	
	AddComponent(ECOMP_RENDER);
	AddComponent(ECOMP_COLLISION);
}

// ------------------------------------
int TerrainChunk::RespondsTo(EMSG m)
// ------------------------------------
{
	switch(m)
	{
	case EMSG_THINK: 
	case EMSG_RENDER: 
	case EMSG_COLLISION:
		return true;
	default:
		return false;
	}
}
