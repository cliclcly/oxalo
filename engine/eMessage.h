// ****************************************************************************
// eMessage.h
// 
// 
// ****************************************************************************

#ifndef __EMESSAGE_H__
#define __EMESSAGE_H__

#include "enums.h"

#include <GL/gl.h>

class CollisionInfo;


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
	RenderMessage(EMSG type);
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

class DieMessage : public Message
{
public:
	DieMessage();
	
};

class ChangeAnimMessage : public Message
{
public:
	ChangeAnimMessage(ANIM,int);
	
	ANIM changeAnim;
	int startFrame;
};

#endif
