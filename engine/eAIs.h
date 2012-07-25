// ****************************************************************************
// eAIs.h
//
//
// ****************************************************************************

#ifndef __EAIS_H__
#define __EAIS_H__

#include "eComponent.h"
#include "eAttribute.h"


// ------------------------------------
class SlimeAIComponent : public Component
// ------------------------------------
{
public:
	SlimeAIComponent();
	
	virtual void HandleMsg(Message* );
	
	float waitTime;
	SpatialAttr* m_spatial;
	PhysicAttr* m_physic;
	StateAttr* m_state;
	float jumpPower;
	float movePower;
};


//------------  MODEL FOR AI ------------

// ------------------------------------
class EnemyAIComponent : public Component
// ------------------------------------
{
public:
	EnemyAIComponent();
	
	virtual void HandleMsg(Message* );
};


#endif