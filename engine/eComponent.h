// ****************************************************************************
// eComponent.h
//
//
// ****************************************************************************

#ifndef __ECOMPONENT_H__
#define __ECOMPONENT_H__

#include "enums.h"

#include <vector>
#include "eMessage.h"
#include "eAttribute.h"
#include "ePolygon.h"
#include "eAnimationObject.h"

class AbstractObject;
class Box;



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
class DropComponent : public Component
// ------------------------------------
{
public:
	DropComponent();
	
	virtual void HandleMsg(Message* );
	
	DropAttr* m_drop;
	
};

// ------------------------------------
class HP_HUDComponent : public Component
// ------------------------------------
{
public:
	HP_HUDComponent();
	
	virtual void HandleMsg(Message* );
	
	HPAttr* m_hp;
};


// ------------------------------------
class AIComponent : public Component
// ------------------------------------
{
public:
	AIComponent();
	
	virtual void HandleMsg(Message* );
	
};

// ------------------------------------
class AnimateComponent : public Component
// ------------------------------------
{
public:

	AnimateComponent();
	
	virtual void HandleMsg(Message* );
	GLuint ChangeAnimation(ANIM);
	
	AnimationSet * m_animation;
	
	int m_currentFrame;
	ANIM m_currentAnimation;
	float m_accum_wait;
	int m_numFrames;
	int m_framerate;
	
	SpatialAttr* m_spatial;
	GeomAttr* m_geom;
	TexAttr* m_tex;
	TypeAttr* m_type;
	
	bool m_animInfoSet;
	
	char* Object;
	COLOR color;
	
};
#endif
