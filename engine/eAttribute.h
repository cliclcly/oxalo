// ****************************************************************************
// eAttribute.h
// 
// 
// ****************************************************************************

#ifndef __EATTRIBUTE_H__
#define __EATTRIBUTE_H__

#include "ePolygon.h"
#include <vector>

class Box;

enum EATTR 
{
	EATTR_DEFAULT,
	EATTR_SPATIAL,
	EATTR_PHYSIC,
	EATTR_GEOM,
<<<<<<< HEAD
	EATTR_TEX
=======
	EATTR_STATE
>>>>>>> bd66b3cbe5056ab0f1c1f36bee70860783cfdc6a
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
	std::vector<EATTR > reqs;
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
	Vector2 lastpos;
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

// ------------------------------------
class TexAttr : public Attribute
// ------------------------------------
{
public:
	TexAttr();
	TexAttr(char*);
	
	virtual int IsAttribute(EATTR a);
	
	char* m_texture_path;
};

// ------------------------------------
class StateAttr : public Attribute
// ------------------------------------
{
public:
	StateAttr();
	
	virtual int IsAttribute(EATTR a);
	
	int falling;
	int jumping;
	int resting;
};

#endif
