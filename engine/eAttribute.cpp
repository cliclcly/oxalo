// ****************************************************************************
// eAttribute.cpp
//
//
// ****************************************************************************

#include "eAttribute.h"
#include "ePolygon.h"

// ------------------------------------
Attribute::Attribute() :
// ------------------------------------
	type(EATTR_DEFAULT)
{
	
}

// ------------------------------------
Attribute::Attribute(EATTR a) :
// ------------------------------------
	type(a)
{

}

// ------------------------------------
Attribute* Attribute::GetNewAttribute(EATTR a)
// ------------------------------------
{
	if (a == EATTR_SPATIAL)
		return new SpatialAttr();
	if (a == EATTR_PHYSIC)
		return new PhysicAttr();
}

// ------------------------------------
SpatialAttr::SpatialAttr() :
// ------------------------------------
	Attribute(EATTR_SPATIAL),
	pos(Vector2(0, 0))
{

}

// ------------------------------------
SpatialAttr::SpatialAttr(float x, float y) :
// ------------------------------------
	Attribute(EATTR_SPATIAL),
	pos(Vector2(x, y))
{

}

// ------------------------------------
int SpatialAttr::IsAttribute(EATTR a)
// ------------------------------------
{
	if (a == EATTR_SPATIAL) return true;
	return false;
}

// ------------------------------------
PhysicAttr::PhysicAttr() :
// ------------------------------------
	Attribute(EATTR_PHYSIC),
	vel(Vector2(0, 0)),
	accel(Vector2(0, 0))
{

}

// ------------------------------------
int PhysicAttr::IsAttribute(EATTR a)
// ------------------------------------
{
	if (a == EATTR_PHYSIC) return true;
	return false;
}

// ------------------------------------
GeomAttr::GeomAttr() :
// ------------------------------------
	Attribute(EATTR_GEOM),
	m_shape(GEOM_SQUARE),
	m_bound(new Box(Vector2(-0.5, -0.5), Vector2(1, 1)))
{

}

// ------------------------------------
GeomAttr::GeomAttr(GEOM g) :
// ------------------------------------
	Attribute(EATTR_GEOM),
	m_shape(g)
{
	switch(g)
	{
	case GEOM_SQUARE:
		m_bound = new Box(Vector2(-0.5, -0.5), Vector2(1, 1));
		break;
	case GEOM_TRIANGLE:
		m_bound = new Box(Vector2(-0.5, -0.5), Vector2(1, 1));
		break;
	}
}

// ------------------------------------
int GeomAttr::IsAttribute(EATTR a)
// ------------------------------------
{
	if (a == EATTR_GEOM) return true;
	return false;
}
