// ****************************************************************************
// eMessage.h
// 
// 
// ****************************************************************************

#ifndef __EMESSAGE_H__
#define __EMESSAGE_H__

enum EMSG
{
	EMSG_DEFAULT,
	EMSG_RENDER,
	EMSG_THINK,
	EMSG_CAMERABLE,
	EMSG_PHYSIC
};

class Message
{
public:
	Message();
	
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

#endif
