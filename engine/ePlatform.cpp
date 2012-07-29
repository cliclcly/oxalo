// ****************************************************************************
// ePlatform.cpp
//
//
// ****************************************************************************

#include "ePlatform.h"

// ------------------------------------
Platform::Platform() :
// ------------------------------------
	_base(Vector2(0, 0)),
	_dim(Vector2(0.5, 2))
{
	Box* b = new Box( Vector2(0, 0), Vector2(0.5, 2));
	GeomAttr* g = new GeomAttr(b);
	AddAttribute(g);
	AddAttribute(new SpatialAttr(0, 0));
	AddAttribute(new TexAttr("Textures/default.png"));
	
	AddComponent(ECOMP_RENDER);
	AddComponent(ECOMP_COLLISION);
}

// ------------------------------------
Platform::Platform(Vector2 base, Vector2 dim) :
// ------------------------------------
	_base(base),
	_dim(dim)
{
	Box* b = new Box( Vector2(0, 0), dim);
	GeomAttr* g = new GeomAttr(b);
	AddAttribute(g);
	AddAttribute(new SpatialAttr(base.x, base.y));
	AddAttribute(new TexAttr("Textures/default.png"));
	
	AddComponent(ECOMP_RENDER);
	AddComponent(ECOMP_COLLISION);
}

// ------------------------------------
int Platform::RespondsTo(EMSG m)
// ------------------------------------
{
	switch (m)
	{
	case EMSG_RENDER:
	case EMSG_THINK:
	case EMSG_COLLISION:
		return true;
	default:
		return false;
	}
}
