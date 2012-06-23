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
void AbstractObject::HandleMsg(Message* m)
// ------------------------------------
{
	std::vector<Component* >::iterator it;
	for (it = m_comps.begin(); it != m_comps.end(); it++)
	{
		(*it)->HandleMsg(m);
	}
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
		Attribute* ar;
		if (!HasAttribute(*it))
			ar = Attribute::GetNewAttribute(*it);
		else
			ar = GetAttribute(*it);
			
		comp->SetAttribute(ar);
	}
	
	m_comps.push_back(comp);	
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
Attribute* AbstractObject::AddAttribute(EATTR a)
// ------------------------------------
{
	if (!HasAttribute(a))
	{
		Attribute* attr = Attribute::GetNewAttribute(a);
		m_attrs.push_back(attr);
		return attr;
	}
	return NULL;
}

// ------------------------------------
int AbstractObject::AddAttribute(Attribute* a)
// ------------------------------------
{
	if (a && !HasAttribute(a->type))
	{
		m_attrs.push_back(a);
		return true;
	}
	return false;
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
	AddAttribute(new GeomAttr(GEOM_SQUARE));
	
	AddComponent(ECOMP_RENDER);
}

// ------------------------------------
Square::Square(float x, float y) :
// ------------------------------------
	m_camera(0)
{
	AddAttribute(new SpatialAttr(x, y));
	AddAttribute(new GeomAttr(GEOM_SQUARE));
	
	AddComponent(ECOMP_RENDER);
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
Triangle::Triangle() :
// ------------------------------------
	m_camera(0)
{
	AddAttribute(new SpatialAttr(0, 0));
	AddAttribute(new GeomAttr(GEOM_TRIANGLE));
	
	AddComponent(ECOMP_RENDER);
}

// ------------------------------------
Triangle::Triangle(float x, float y) :
// ------------------------------------
	m_camera(0)
{
	AddAttribute(new SpatialAttr(x, y));
	AddAttribute(new GeomAttr(GEOM_TRIANGLE));
	
	AddComponent(ECOMP_RENDER);
}

// ------------------------------------
int Triangle::RespondsTo(EMSG m)
// ------------------------------------
{
	if (m == EMSG_RENDER || 
		m == EMSG_THINK ||
		m == EMSG_CAMERABLE)
		return true;
}

// ------------------------------------
Camera* Triangle::GetCamera()
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
	AddComponent(ECOMP_PHYSIC);
}

// ------------------------------------
PSquare::PSquare(float x, float y) :
// ------------------------------------
	Square(x, y)
{
	AddAttribute(new PhysicAttr());
	AddComponent(ECOMP_PHYSIC);
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
