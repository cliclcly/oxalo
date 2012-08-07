// ****************************************************************************
// eAttribute.cpp
//
//
// ****************************************************************************

#include "eAttribute.h"
#include "ePolygon.h"
#include "eEngineclass.h"

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
	if (a == EATTR_DROP)
		return new DropAttr();
	if (a == EATTR_TYPE)
		return new TypeAttr();
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
	Attribute(EATTR_TEXTURE)
{
	m_texture = ilutGLLoadImage((char*)"Textures/default.png");
	m_tex_coord_x1=0;
	m_tex_coord_x2=1;
	m_tex_coord_y1=0;
	m_tex_coord_y2=1;
}

// ------------------------------------
TexAttr::TexAttr(std::string path) :
// ------------------------------------
	Attribute(EATTR_TEXTURE)
{
	m_texture = ilutGLLoadImage((char*)path.c_str());
	m_tex_coord_x1=0;
	m_tex_coord_x2=1;
	m_tex_coord_y1=0;
	m_tex_coord_y2=1;
}	

// ------------------------------------
TexAttr::TexAttr(std::string objType, COLOR color) :
// ------------------------------------
	Attribute(EATTR_TEXTURE)
{
	std::string path = "Textures/";
	path+= objType;
	path+= "/";
	if (color >= 0)
	{
		path+= EngineClass::colorString[color];
		path+="/";
	}
	path+="default.png";
	m_texture = ilutGLLoadImage((char*)path.c_str());
	m_tex_coord_x1=0;
	m_tex_coord_x2=1;
	m_tex_coord_y1=0;
	m_tex_coord_y2=1;
}	

// ------------------------------------
void TexAttr::SetTexture(GLuint newTexture)
// ------------------------------------
{
	//printf("current Texture: %u\n", m_texture);
	//printf("setting texture %u\n",newTexture);
	m_texture = newTexture;
	//printf("dooone!\n");
}

// ------------------------------------
GLuint TexAttr::GetTexture()
// ------------------------------------
{
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
DropAttr::DropAttr() :
// ------------------------------------
	Attribute(EATTR_DROP)
{

}

// ------------------------------------
DropAttr::DropAttr(std::vector<int> id, std::vector<float> ic) :
// ------------------------------------
	Attribute(EATTR_DROP),
	ItemDrop(id),
	ItemChance(ic)
{

}

// ------------------------------------
int DropAttr::IsAttribute(EATTR a)
// ------------------------------------
{
	if (a == EATTR_DROP) return true;
	return false;
}
// ------------------------------------
TypeAttr::TypeAttr():
// ------------------------------------
	Attribute(EATTR_TYPE),
	m_type(std::string("default"))
{

}

// ------------------------------------
TypeAttr::TypeAttr(std::string type):
// ------------------------------------
	Attribute(EATTR_TYPE),
	m_type(type)
{

}

// ------------------------------------
int TypeAttr::IsAttribute(EATTR a)
// ------------------------------------
{
	if (a == EATTR_TYPE) return true;
	return false;
}


