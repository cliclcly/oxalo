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
	ECOMP_COLLISION,
	ECOMP_DAMAGEABLE,
	ECOMP_DROPS,
	ECOMP_AI
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
	TexAttr* m_tex;
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
	StateAttr* m_state;
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
	//~CollisionComponent();
	
	virtual void HandleMsg(Message* );
	
	CollisionInfo* GetCollisionInfo();
	
	SpatialAttr* m_spatial;
	GeomAttr* m_geom;
	
	CollisionInfo* m_info;
};

// ------------------------------------
class DamageableComponent : public Component
// ------------------------------------
{
public:
	DamageableComponent();
	
	virtual void HandleMsg(Message* );
	
	HPAttr* m_hp;
	
};

// ------------------------------------
class DropsComponent : public Component
// ------------------------------------
{
public:
	DropsComponent();
	
	virtual void HandleMsg(Message* );
	
	DropsAttr* m_drops;
	
};

// ------------------------------------
class AIComponent : public Component
// ------------------------------------
{
public:
	AIComponent();
	
	virtual void HandleMsg(Message* );
	
};
#endif
