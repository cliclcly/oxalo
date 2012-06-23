// ****************************************************************************
// eComponent.h
//
//
// ****************************************************************************

#ifndef __ECOMPONENT_H__
#define __ECOMPONENT_H__

#include <vector>
#include "eMessage.h"
#include "eAttribute.h"
#include "ePolygon.h"

class AbstractObject;
class Box;

enum ECOMP
{
	ECOMP_DEFAULT,
	ECOMP_RENDER,
	ECOMP_PHYSIC,
	ECOMP_COLLISION
};

// ------------------------------------
class Component
// ------------------------------------
{
public:
	Component();
	Component(ECOMP type);
	
	static Component* GetNewComponent(ECOMP c);

	virtual void HandleMsg(Message* ) = 0;
	
	virtual void SetAttribute(Attribute* ar);
	
	ECOMP type;
	std::vector<EATTR> reqs;
	AbstractObject* parent;
};

// ------------------------------------
class RenderComponent : public Component
// ------------------------------------
{
public:
	RenderComponent();
	
	virtual void HandleMsg(Message* );
	
	SpatialAttr* m_spatial;
	GeomAttr* m_geom;
};

// ------------------------------------
class PhysicComponent : public Component
// ------------------------------------
{
public:
	PhysicComponent();
	
	virtual void HandleMsg(Message* );
	
	SpatialAttr* m_spatial;
	PhysicAttr* m_physic;
};

// ------------------------------------
class CollisionInfo
// ------------------------------------
{
public:
	CollisionInfo();
	
	AbstractObject* other;
	Vector2 pos;
	Vector2 vel;
	Box* bound;
};

// ------------------------------------
class CollisionComponent : public Component
// ------------------------------------
{
public:
	CollisionComponent();
	
	virtual void HandleMsg(Message* );
	
	CollisionInfo* GetCollisionInfo();
	
	SpatialAttr* m_spatial;
};

#endif