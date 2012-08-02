// ****************************************************************************
// eAttribute.h
// 
// 
// ****************************************************************************

#ifndef __EATTRIBUTE_H__
#define __EATTRIBUTE_H__

#include "ePolygon.h"
#include <vector>

#include <GL/gl.h>

class Box;

enum EATTR 
{
	EATTR_DEFAULT,
	EATTR_SPATIAL,
	EATTR_PHYSIC,
	EATTR_GEOM,
	EATTR_TEXTURE,
	EATTR_STATE,
	EATTR_HP,
	EATTR_COLOR,
	EATTR_DROPS
};

enum GEOM
{
	GEOM_SQUARE,
	GEOM_TRIANGLE
};	

enum COLOR
{
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE,
	COLOR_ORANGE,
	COLOR_PURPLE,
	COLOR_YELLOW,
	COLOR_WHITE,
	COLOR_BLACK,
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
	Vector2 lastvel;
};

// ------------------------------------
class GeomAttr : public Attribute
// ------------------------------------
{
public:
	GeomAttr();
	GeomAttr(GEOM);
	GeomAttr(Box );
	
	virtual int IsAttribute(EATTR a);
	
	GEOM m_shape;
	Box m_bound;
	Mesh m_mesh;
};

// ------------------------------------
class TexAttr : public Attribute
// ------------------------------------
{
public:
	TexAttr();
	TexAttr(char*);
	
	virtual int IsAttribute(EATTR a);
	GLuint GetTexture();
	
	char* m_texture_path;
	
private:
	GLuint m_texture;
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
	int jumped;
	int resting;
};

// ------------------------------------
class HPAttr : public Attribute
// ------------------------------------
{
public:
	HPAttr();
	HPAttr(int);
	
	virtual int IsAttribute(EATTR a);
	
	int maxHP;
	int currentHP;
	
};
	
// ------------------------------------
class ColorAttr : public Attribute
// ------------------------------------
{
public:
	ColorAttr();
	ColorAttr(COLOR);
	
	virtual int IsAttribute(EATTR a);
	
	COLOR m_color;
	
};

// ------------------------------------
class DropsAttr : public Attribute
// ------------------------------------
{
public:
	DropsAttr();
	DropsAttr(std::vector<int>,std::vector<float>);
	
	virtual int IsAttribute(EATTR a);
	
	std::vector<int> ItemDrops;
	std::vector<float> ItemChances;
	
};
#endif
