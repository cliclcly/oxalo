// ****************************************************************************
// eAttribute.h
// 
// 
// ****************************************************************************

#ifndef __EATTRIBUTE_H__
#define __EATTRIBUTE_H__

#include "enums.h"

#include "ePolygon.h"
#include <vector>
#include <string>
#include "iLoggable.h"

#include <GL/gl.h>

class Box;

// ------------------------------------
class Attribute : public iLoggable
// ------------------------------------
{
public:
	Attribute();
	Attribute(EATTR a);

	virtual int IsAttribute(EATTR a) = 0;
	
	static Attribute* GetNewAttribute(EATTR a);
	
	virtual std::string Log(int fields[], int size);
	
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
class DropAttr : public Attribute
// ------------------------------------
{
public:
	DropAttr();
	DropAttr(std::vector<int>,std::vector<float>);
	
	virtual int IsAttribute(EATTR a);
	
	std::vector<int> ItemDrop;
	std::vector<float> ItemChance;
	
};

// ------------------------------------
class TexAttr : public Attribute
// ------------------------------------
{
public:
	TexAttr();
	TexAttr(std::string);
	TexAttr(std::string,COLOR);
	
	virtual int IsAttribute(EATTR a);
	GLuint GetTexture();
	void SetTexture(GLuint);
	
	float m_tex_coord_x1, m_tex_coord_x2;
	float m_tex_coord_y1, m_tex_coord_y2;
	GLuint m_texture;
	
	
private:
};

// ------------------------------------
class TypeAttr : public Attribute
// ------------------------------------
{
public:
	TypeAttr();
	TypeAttr(std::string);
	
	virtual int IsAttribute(EATTR a);
	
	std::string m_type;
	
};
#endif
