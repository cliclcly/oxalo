// ****************************************************************************
// eAttribute.cpp
//
//
// ****************************************************************************

#include "eAttribute.h"
#include "ePolygon.h"

#include <IL/ilut.h>

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
	if (a == EATTR_GEOM)
		return new GeomAttr();
	if (a == EATTR_STATE)
		return new StateAttr();
	if (a == EATTR_TEXTURE)
		return new TexAttr();
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
	accel(Vector2(0, 0)),
	lastpos(Vector2(0, 0)),
	lastvel(Vector2(0, 0))
{
	reqs.push_back(EATTR_SPATIAL);
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
GeomAttr::GeomAttr(Box* b) :
// ------------------------------------
	Attribute(EATTR_GEOM),
	m_shape(GEOM_SQUARE)
{
	if (b)
		m_bound = b;
	else
		m_bound = new Box(Vector2(-0.5, -0.5), Vector2(1, 1));
}

// ------------------------------------
int GeomAttr::IsAttribute(EATTR a)
// ------------------------------------
{
	if (a == EATTR_GEOM) return true;
	return false;
}

// ------------------------------------
TexAttr::TexAttr() :
// ------------------------------------
	Attribute(EATTR_TEXTURE),
	m_texture_path(0),
	m_texture(0)
{

}	

// ------------------------------------
TexAttr::TexAttr(char* path) :
// ------------------------------------
	Attribute(EATTR_TEXTURE),
	m_texture_path(path),
	m_texture(0)
{

}	

// ------------------------------------
GLuint TexAttr::GetTexture()
// ------------------------------------
{
	if (!m_texture)
	{
		if (m_texture_path)
		{
			m_texture = ilutGLLoadImage(m_texture_path);
		}
		else
		{
			m_texture = ilutGLLoadImage((char*)"default.png");
		}
	}
	return m_texture;
}

// ------------------------------------
int TexAttr::IsAttribute(EATTR a)
// ------------------------------------
{
	if (a == EATTR_TEXTURE) return true;
}

	
// ------------------------------------
StateAttr::StateAttr() :
// ------------------------------------
	Attribute(EATTR_STATE),
	falling(true),
	jumping(false),
	jumped(true),
	resting(false)
{

}

// ------------------------------------
int StateAttr::IsAttribute(EATTR a)
// ------------------------------------
{
	if (a == EATTR_STATE)
		return true;
	return false;
}
