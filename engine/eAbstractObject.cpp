// ****************************************************************************
// eAbstractObject.cpp
//
//
// ****************************************************************************

#include "eAbstractObject.h"

#include "eEngineClass.h"
#include <stdio.h>

// ------------------------------------
AbstractObject::AbstractObject()
// ------------------------------------
{
	EngineClass* instance = EngineClass::Instance();
	GUID = instance->GetNextGUID();
}

// ------------------------------------
int AbstractObject::HasComponent(ECOMP c)
// ------------------------------------
{
	std::vector<Component* >::iterator it;
	for (it = m_comps.begin(); it != m_comps.end(); it++)
	{
		if ((*it)->type == c)
			return true;
	}
	return false;
}

// ------------------------------------
int AbstractObject::AddComponent(ECOMP c)
// ------------------------------------
{
	Component* comp = Component::GetNewComponent(c);
	if (!comp) return false;
	
	// ensure all attributes are present
	std::vector<EATTR>::iterator it;
	for (it = comp->reqs.begin(); it != comp->reqs.end(); it++)
	{
	
	}
	
}

// ------------------------------------
int AbstractObject::HasAttribute(EATTR a)
// ------------------------------------
{
	std::vector<Attribute* >::iterator it;
	for (it = m_attrs.begin(); it != m_attrs.end(); it++)
	{
		if ((*it)->IsAttribute(a)) return true;
	}
	
	return false;
}

// ------------------------------------
void AbstractObject::AddAttribute(EATTR a)
// ------------------------------------
{
	if (!HasAttribute(a))
		m_attrs.push_back(Attribute::GetNewAttribute(a));
}

// ------------------------------------
void AbstractObject::AddAttribute(Attribute* a)
// ------------------------------------
{
	if (a && !HasAttribute(a->type))
		m_attrs.push_back(a);
}

// ------------------------------------
Attribute* AbstractObject::GetAttribute(EATTR a)
// ------------------------------------
{
	std::vector<Attribute* >::iterator it;
	for (it = m_attrs.begin(); it != m_attrs.end(); it++)
	{
		if ((*it)->type ==  a)
			return (*it);
	}
	
	return NULL;
}

// ------------------------------------
Square::Square() :
// ------------------------------------
	m_camera(0)
{
	AddAttribute(new SpatialAttr(0, 0));
}

// ------------------------------------
Square::Square(float x, float y) :
// ------------------------------------
	m_camera(0)
{
	AddAttribute(new SpatialAttr(x, y));
}

// ------------------------------------
int Square::RespondsTo(EMSG m)
// ------------------------------------
{
	if (m == EMSG_RENDER || 
		m == EMSG_THINK ||
		m == EMSG_CAMERABLE)
		return true;
}

// ------------------------------------
void Square::HandleMsg(Message* m)
// ------------------------------------
{
	if (m->type == EMSG_RENDER)
		Render(m);	
	else if (m->type == EMSG_THINK)
		Think(m);
}

// ------------------------------------
void Square::Think(Message* m)
// ------------------------------------
{

}

// ------------------------------------
void Square::Render(Message* m)
// ------------------------------------
{
	SpatialAttr* sq = 
		static_cast<SpatialAttr* >(GetAttribute(EATTR_SPATIAL));
	glPushMatrix();
	glTranslatef(sq->m_x, sq->m_y, 0);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	
	glBegin(GL_QUADS);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);
	glEnd();
	
	glPopMatrix();
}

// ------------------------------------
Camera* Square::GetCamera()
// ------------------------------------
{
	SpatialAttr* sa = 	
		static_cast<SpatialAttr* >(GetAttribute(EATTR_SPATIAL));

	if (!m_camera)
	{
		m_camera = new Camera(&(sa->m_x), &(sa->m_y), new float(4.0));
	}
	return m_camera;
}

// ------------------------------------
PSquare::PSquare() :
// ------------------------------------
	Square(10, 12)
{
	AddAttribute(new PhysicAttr());
}

// ------------------------------------
PSquare::PSquare(float x, float y) :
// ------------------------------------
	Square(x, y)
{
	AddAttribute(new PhysicAttr());
}

// ------------------------------------
int PSquare::RespondsTo(EMSG m)
// ------------------------------------
{
	if (m == EMSG_THINK ||
		m == EMSG_RENDER ||
		m == EMSG_CAMERABLE ||
		m == EMSG_PHYSIC)
		return true;
}

// ------------------------------------
void PSquare::HandleMsg(Message* m)
// ------------------------------------
{
	if (m->type == EMSG_THINK)
		Think(m);
	else if (m->type == EMSG_RENDER)
		Render(m);
}

// ------------------------------------
void PSquare::Think(Message* m)
// ------------------------------------
{
	SpatialAttr* sa = 
		static_cast<SpatialAttr* >(GetAttribute(EATTR_SPATIAL));
	PhysicAttr* pa = 
		static_cast<PhysicAttr* >(GetAttribute(EATTR_PHYSIC));
	ThinkMessage* tm = static_cast<ThinkMessage* >(m);
	pa->m_dy += -1 * tm->m_diff;
	sa->m_y += pa->m_dy * tm->m_diff;
}
