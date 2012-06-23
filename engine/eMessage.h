// ****************************************************************************
// eMessage.h
// 
// 
// ****************************************************************************

#ifndef __EMESSAGE_H__
#define __EMESSAGE_H__

class CollisionInfo;

enum EMSG
{
	EMSG_DEFAULT,
	EMSG_RENDER,
	EMSG_THINK,
	EMSG_CAMERABLE,
	EMSG_PHYSIC,
	EMSG_COLLISION
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
	ThinkMessage(float );

	float m_diff;
};

class CamerableMessage : public Message
{
public:
	CamerableMessage();
};

class CollisionMessage : public Message
{
public:
	CollisionMessage( float, CollisionInfo* );
	
	float diff;
	CollisionInfo* info;
};

#endif
