// ****************************************************************************
// eAIs.h
//
//
// ****************************************************************************

#ifndef __EAIS_H__
#define __EAIS_H__


// ------------------------------------
class SlimeAIComponent : public Component()
// ------------------------------------
{
public:
	SlimeAIComponent();
	
	virtual void HandleMsg(Message* );
};


//------------  MODEL FOR AI ------------

// ------------------------------------
class EnemyAIComponent : public Component()
// ------------------------------------
{
public:
	EnemyAIComponent();
	
	virtual void HandleMsg(Message* );
};

#endif