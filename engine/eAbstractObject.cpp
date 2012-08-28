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
	if (!comp) 
	{
		return false;
	}
	
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
	
	// set parent
	comp->parent = this;
	
	m_comps.push_back(comp);	
}

// ------------------------------------
Component* AbstractObject::GetComponent(ECOMP c)
// -----------------------------------
{
	std::vector<Component* >::iterator it;
	for (it = m_comps.begin(); it != m_comps.end(); it++)
	{
		if ((*it)->type == c)
			return (*it);
	}
	
	return NULL;
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
		std::vector<EATTR >::iterator it;
		for (it = attr->reqs.begin(); it != attr->reqs.end(); it++)
		{
			if (!HasAttribute(*it))
				AddAttribute(*it);
		}
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
		std::vector<EATTR >::iterator it;
		for (it = a->reqs.begin(); it != a->reqs.end(); it++)
		{
			if (!HasAttribute(*it))
				AddAttribute(*it);
		}
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
std::string AbstractObject::Log(int fields[], int size)
// ------------------------------------
{
	std::string toReturn = "";
	for(int i=0;i<size;i++)
	{
		switch(fields[i])
		{
			case LOGGER_EATTR_DEFAULT:
				if (HasAttribute(EATTR_DEFAULT))
				{
					int fields[] = {0};
					toReturn+= GetAttribute(EATTR_DEFAULT)->Log(fields,1);
				}
				break;
			case LOGGER_EATTR_SPATIAL:
				if (HasAttribute(EATTR_SPATIAL))
				{
					int fields[] = {0};
					toReturn+= GetAttribute(EATTR_SPATIAL)->Log(fields,1);
				}
				break;
			case LOGGER_EATTR_PHYSIC:
				if (HasAttribute(EATTR_PHYSIC))
				{
					int fields[] = {0};
					toReturn+= GetAttribute(EATTR_PHYSIC)->Log(fields,1);
				}
				break;
			case LOGGER_EATTR_GEOM:
				if (HasAttribute(EATTR_GEOM))
				{
					int fields[] = {0};
					toReturn+= GetAttribute(EATTR_GEOM)->Log(fields,1);
				}
				break;
			case LOGGER_EATTR_TEXTURE:
				if (HasAttribute(EATTR_TEXTURE))
				{
					int fields[] = {0};
					toReturn+= GetAttribute(EATTR_TEXTURE)->Log(fields,1);
				}
				break;
			case LOGGER_EATTR_STATE:
				if (HasAttribute(EATTR_STATE))
				{
					int fields[] = {0};
					toReturn+= GetAttribute(EATTR_STATE)->Log(fields,1);
				}
				break;
			case LOGGER_EATTR_HP:
				if (HasAttribute(EATTR_HP))
				{
					int fields[] = {0};
					toReturn+= GetAttribute(EATTR_HP)->Log(fields,1);
				}
				break;
			case LOGGER_EATTR_COLOR:
				if (HasAttribute(EATTR_COLOR))
				{
					int fields[] = {0};
					toReturn+= GetAttribute(EATTR_COLOR)->Log(fields,1);
				}
				break;
			case LOGGER_EATTR_DROP:
				if (HasAttribute(EATTR_DROP))
				{
					int fields[] = {0};
					toReturn+= GetAttribute(EATTR_DROP)->Log(fields,1);
				}
				break;
			case LOGGER_EATTR_TYPE:
				if (HasAttribute(EATTR_TYPE))
				{
					int fields[] = {0};
					toReturn+= GetAttribute(EATTR_TYPE)->Log(fields,1);
				}
				break;
			
			case LOGGER_ECOMP_DEFAULT:
			
				break;
			case LOGGER_ECOMP_RENDER:
			
				break;
			case LOGGER_ECOMP_RENDER_TEXT:
			
				break;
			case LOGGER_ECOMP_PHYSIC:
			
				break;
			case LOGGER_ECOMP_COLLISION:
			
				break;
			case LOGGER_ECOMP_DAMAGEABLE:
			
				break;
			case LOGGER_ECOMP_DROP:
			
				break;
			case LOGGER_ECOMP_HUD_HP:
			
				break;
			case LOGGER_ECOMP_ANIM:
			
				break;
			case LOGGER_ECOMP_AI:
			
				break;
			case LOGGER_ECOMP_SLIME_AI:
			
				break;
			case LOGGER_ECOMP_ENEMY_AI:
			
				break;
		}
	}
	return toReturn;
};

// ------------------------------------
Square::Square()
// ------------------------------------
{
	AddAttribute(new SpatialAttr(0, 0));
	AddAttribute(new GeomAttr(GEOM_SQUARE));
	
	AddComponent(ECOMP_RENDER);
	AddComponent(ECOMP_COLLISION);
}

// ------------------------------------
Square::Square(float x, float y)
// ------------------------------------
{
	AddAttribute(new SpatialAttr(x, y));
	AddAttribute(new GeomAttr(GEOM_SQUARE));
	
	AddComponent(ECOMP_RENDER);
	AddComponent(ECOMP_COLLISION);
}

// ------------------------------------
int Square::RespondsTo(EMSG m)
// ------------------------------------
{
	if (m == EMSG_RENDER || 
		m == EMSG_THINK ||
		m == EMSG_SPATIAL ||
		m == EMSG_COLLISION)
		return true;
	return false;
}

// ------------------------------------
Triangle::Triangle()
// ------------------------------------
{
	AddAttribute(new SpatialAttr(0, 0));
	AddAttribute(new GeomAttr(GEOM_TRIANGLE));
	
	AddComponent(ECOMP_RENDER);
}

// ------------------------------------
Triangle::Triangle(float x, float y)
// ------------------------------------
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
		m == EMSG_SPATIAL)
		return true;
	return false;
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
		m == EMSG_SPATIAL ||
		m == EMSG_PHYSIC ||
		m == EMSG_COLLISION)
		return true;
	return false;
}
