// ****************************************************************************
// eMessage.h
// 
// 
// ****************************************************************************

#ifndef __EMESSAGE_H__
#define __EMESSAGE_H__

#include <GL/gl.h>

class CollisionInfo;

enum EMSG
{
	EMSG_DEFAULT,
	EMSG_RENDER,
	EMSG_THINK,
	EMSG_SPATIAL,
	EMSG_PHYSIC,
	EMSG_COLLISION,
	EMSG_KEYBOARD,
	EMSG_STATE,
	EMSG_DROP,
	EMSG_DAMAGE
};

class Message
{
public:
	Message();
	Message(EMSG m);
	
	EMSG type;
};

class RenderMessage : public Message
{
public:
	RenderMessage();
};

class ThinkMessage : public Message
{
public:
	ThinkMessage( float, int);

	float m_diff;
	int tock;
};

class CollisionMessage : public Message
{
public:
	CollisionMessage( float, CollisionInfo* );
	
	float diff;
	CollisionInfo* info;
};

class KeyboardMessage : public Message
{
public:
	KeyboardMessage( GLubyte key, int x, int y, int down);
	
	GLubyte key;
	int x;
	int y;
	int down;
};

class DamageMessage : public Message
{
public:
	DamageMessage(int damage);
	
	int damage;
};

class DropMessage : public Message
{
public:
	DropMessage();
	
};
#endif
