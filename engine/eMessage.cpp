// *****************************************************************************
// eMessage.cpp
//
//
// ****************************************************************************

#include "eMessage.h"

// ------------------------------------
Message::Message()
// ------------------------------------
{
	type = EMSG_DEFAULT;
}

// ------------------------------------
Message::Message(EMSG m) :
// ------------------------------------
	type(m)
{

}

// ------------------------------------
RenderMessage::RenderMessage() :
// ------------------------------------
	Message(EMSG_RENDER)
{

}

// ------------------------------------
ThinkMessage::ThinkMessage(float diff) : 
// ------------------------------------
	Message(EMSG_THINK),
	m_diff(diff)
{

}

// ------------------------------------
CamerableMessage::CamerableMessage() :
// ------------------------------------
	Message(EMSG_CAMERABLE)
{

}

// ------------------------------------
CollisionMessage::CollisionMessage(CollisionInfo* c) :
// ------------------------------------
	Message(EMSG_COLLISION),
	info(c)
{

}
