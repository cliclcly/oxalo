// ****************************************************************************
// eAttribute.h
// 
// 
// ****************************************************************************

#ifndef __EATTRIBUTE_H__
#define __EATTRIBUTE_H__

#include "ePolygon.h"

class Box;

enum EATTR 
{
	EATTR_DEFAULT,
	EATTR_SPATIAL,
	EATTR_PHYSIC,
	EATTR_GEOM
};

enum GEOM
{
	GEOM_SQUARE,
	GEOM_TRIANGLE
};	

// ------------------------------------
class Attribute
// ------------------------------------
{
public:
	Attribute();
	Attribute(EATTR a);

	virtual int IsAttribute(EATTR a) = 0;
	
	static Attribute* GetNewAttribute(EATTR a);
	
	EATTR type;
};

// ------------------------------------
class SpatialAttr : public Attribute
// ------------------------------------
{
public:
	SpatialAttr();
	SpatialAttr(float, float);

	virtual int IsAttribute(EATTR a);
	
	Vector2 pos;
};

// ------------------------------------
class PhysicAttr : public Attribute
// ------------------------------------
{
public:
	PhysicAttr();
	
	virtual int IsAttribute(EATTR a);
	
	Vector2 vel;
	Vector2 accel;
};

// ------------------------------------
class GeomAttr : public Attribute
// ------------------------------------
{
public:
	GeomAttr();
	GeomAttr(GEOM);
	
	virtual int IsAttribute(EATTR a);
	
	GEOM m_shape;
	Box* m_bound;
};

#endif
