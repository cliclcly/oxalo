// ****************************************************************************
// eComponent.cpp
//
//
// ****************************************************************************

#include "eComponent.h"
#include "eAbstractObject.h"
#include "eDebug.h"

#include <windows.h>
#include <GL/glut.h>

// ------------------------------------
Component::Component() :
// ------------------------------------
	type(ECOMP_DEFAULT)
{
	
}

// ------------------------------------
Component::Component(ECOMP type) :
// ------------------------------------
	type(type)
{

}

// ------------------------------------
Component* Component::GetNewComponent(ECOMP c)
// ------------------------------------
{
	if (c ==  ECOMP_RENDER)
		return new RenderComponent();
	if (c == ECOMP_PHYSIC)
		return new PhysicComponent();
	if (c == ECOMP_COLLISION)
		return new CollisionComponent();
}

// ------------------------------------
void Component::SetAttribute(Attribute* ar)
// ------------------------------------
{
	if (type == ECOMP_RENDER)
	{
		RenderComponent* rc = static_cast<RenderComponent* >(this);
		if (ar->type == EATTR_SPATIAL)
			rc->m_spatial = static_cast<SpatialAttr* >(ar);
		if (ar->type == EATTR_GEOM)
			rc->m_geom = static_cast<GeomAttr* >(ar);
	}
	if (type == ECOMP_PHYSIC)
	{
		PhysicComponent* pc = static_cast<PhysicComponent* >(this);
		if (ar->type == EATTR_SPATIAL)
			pc->m_spatial = static_cast<SpatialAttr* >(ar);
		if (ar->type == EATTR_PHYSIC)
			pc->m_physic = static_cast<PhysicAttr* >(ar);
	}
	if (type == ECOMP_COLLISION)
	{
		CollisionComponent* cc = static_cast<CollisionComponent* >(this);
		if (ar->type == EATTR_SPATIAL)
			cc->m_spatial = static_cast<SpatialAttr* >(ar);
	}
}

// ------------------------------------
RenderComponent::RenderComponent() :
// ------------------------------------
	Component(ECOMP_RENDER)
{
	reqs.push_back(EATTR_SPATIAL);
	reqs.push_back(EATTR_GEOM);
}

// ------------------------------------
void RenderComponent::HandleMsg(Message* m)
// ------------------------------------
{
	if (m->type == EMSG_RENDER)
	{
		switch(m_geom->m_shape)
		{
			case GEOM_SQUARE:
				glPushMatrix();	
				glTranslatef(m_spatial->m_x, m_spatial->m_y, 0);
				glColor4f(1.0, 0.0, 0.0, 1.0);
				
				glBegin(GL_QUADS);
					glVertex2f(-0.5, -0.5);
					glVertex2f(-0.5, 0.5);
					glVertex2f(0.5, 0.5);
					glVertex2f(0.5, -0.5);
				glEnd();
				
				glPopMatrix();
				break;
			case GEOM_TRIANGLE:
				glPushMatrix();	
				glTranslatef(m_spatial->m_x, m_spatial->m_y, 0);
				glColor4f(1.0, 0.0, 0.0, 1.0);
				
				glBegin(GL_TRIANGLES);
					glVertex2f(0,.5);
					glVertex2f(.5,-.5);
					glVertex2f(-.5,-.5);
				glEnd();
				
				glPopMatrix();
				break;
		}
	}
}

// ------------------------------------
PhysicComponent::PhysicComponent() :
// ------------------------------------
	Component(ECOMP_PHYSIC)
{
	reqs.push_back(EATTR_SPATIAL);
	reqs.push_back(EATTR_PHYSIC);
}

// ------------------------------------
void PhysicComponent::HandleMsg(Message* m)
// ------------------------------------
{
	if (m->type == EMSG_THINK)
	{
		ThinkMessage* tm = static_cast<ThinkMessage* >(m);
		m_physic->m_dy += -1 * tm->m_diff;
		m_spatial->m_y += m_physic->m_dy * tm->m_diff;
	}
}

// ------------------------------------
CollisionInfo::CollisionInfo() :
// ------------------------------------
	other(0),
	pos(Vector2(0, 0)),
	vel(Vector2(0, 0)),
	bound(new Box(Vector2(0, 0), Vector2(0, 0)))
{
	
}

// ------------------------------------
CollisionComponent::CollisionComponent() :
// ------------------------------------
	Component(ECOMP_COLLISION)
{
	reqs.push_back(EATTR_SPATIAL);
}

// ------------------------------------
void CollisionComponent::HandleMsg(Message* m)
// ------------------------------------
{
	if (m->type == EMSG_COLLISION)
	{
		CollisionMessage* cm = static_cast<CollisionMessage* >(m);
	}
}

// ------------------------------------
CollisionInfo* CollisionComponent::GetCollisionInfo()
// ------------------------------------
{
	CollisionInfo* info = new CollisionInfo();
	info->other = parent;
	
	if (parent->RespondsTo(EMSG_PHYSIC))
	{
		PhysicAttr* pa = 
			static_cast<PhysicAttr* >(parent->GetAttribute(EATTR_PHYSIC));
		info->vel = Vector2(pa->m_dx, pa->m_dy);
	}
	else
	{
		info->vel = Vector2(0, 0);
	}
	
	SpatialAttr* sa = 
		static_cast<SpatialAttr* >(parent->GetAttribute(EATTR_SPATIAL));
	info->pos = Vector2(sa->m_x, sa->m_y);
	
	return info;
}

