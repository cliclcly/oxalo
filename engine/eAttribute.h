// ****************************************************************************
// eAttribute.h
// 
// 
// ****************************************************************************

#ifndef __EATTRIBUTE_H__
#define __EATTRIBUTE_H__

enum EATTR 
{
	EATTR_DEFAULT,
	EATTR_SPATIAL,
	EATTR_PHYSIC
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
	
	float m_x;
	float m_y;
};

// ------------------------------------
class PhysicAttr : public Attribute
// ------------------------------------
{
public:
	PhysicAttr();
	
	virtual int IsAttribute(EATTR a);
	
	float m_dx;
	float m_ddx;
	float m_dy;
	float m_ddy;
};

#endif
