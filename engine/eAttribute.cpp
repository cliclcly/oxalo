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
	if (a == EATTR_HP)
		return new HPAttr();
	if (a == EATTR_COLOR)
		return new ColorAttr();
	if (a == EATTR_DROPS)
		return new DropsAttr();
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
	m_bound(Box(Vector2(-0.5, -0.5), Vector2(1, 1)))
{
	m_mesh = Mesh(m_bound);
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
		m_bound = Box(Vector2(-0.5, -0.5), Vector2(1, 1));
		m_mesh = Mesh(m_bound);
		break;
	case GEOM_TRIANGLE:
		m_bound = Box(Vector2(-0.5, -0.5), Vector2(1, 1));
		m_mesh = Mesh(m_bound);
		break;
	}
}

// ------------------------------------
GeomAttr::GeomAttr(Box b) :
// ------------------------------------
	Attribute(EATTR_GEOM),
	m_shape(GEOM_SQUARE)
{
	m_bound = b;
	m_mesh = Mesh(b);
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
	return false;
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

// ------------------------------------
HPAttr::HPAttr() :
// ------------------------------------
	Attribute(EATTR_HP),
	maxHP(100),
	currentHP(100)
{

}

// ------------------------------------
HPAttr::HPAttr(int HP) :
// ------------------------------------
	Attribute(EATTR_HP),
	maxHP(HP),
	currentHP(HP)
{
	
}

// ------------------------------------
int HPAttr::IsAttribute(EATTR a)
// ------------------------------------
{
	if (a == EATTR_HP) return true;
	return false;
}

// ------------------------------------
ColorAttr::ColorAttr() :
// ------------------------------------
	Attribute(EATTR_COLOR),
	m_color(COLOR_WHITE)
{

}

// ------------------------------------
ColorAttr::ColorAttr(COLOR c) :
// ------------------------------------
	Attribute(EATTR_COLOR),
	m_color(c)
{
	
}

// ------------------------------------
int ColorAttr::IsAttribute(EATTR a)
// ------------------------------------
{
	if (a == EATTR_COLOR) return true;
	return false;
}

// ------------------------------------
DropsAttr::DropsAttr() :
// ------------------------------------
	Attribute(EATTR_DROPS)
{

}

// ------------------------------------
DropsAttr::DropsAttr(std::vector<int> id, std::vector<float> ic) :
// ------------------------------------
	Attribute(EATTR_DROPS),
	ItemDrops(id),
	ItemChances(ic)
{

}

// ------------------------------------
int DropsAttr::IsAttribute(EATTR a)
// ------------------------------------
{
	if (a == EATTR_DROPS) return true;
	return false;
}
