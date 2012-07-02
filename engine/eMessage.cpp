// *****************************************************************************
// eMessage.cpp
//
//
// ****************************************************************************

#include "eMessage.h"
#include "eComponent.h"

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
ThinkMessage::ThinkMessage(float diff, int tock) : 
// ------------------------------------
	Message(EMSG_THINK),
	m_diff(diff),
	tock(tock)
{

}

// ------------------------------------
CollisionMessage::CollisionMessage( float d, CollisionInfo* c) :
// ------------------------------------
	Message(EMSG_COLLISION),
	diff(d),
	info(c)
{

}

// ------------------------------------
KeyboardMessage::KeyboardMessage( GLubyte key, int x, int y, int down) :
// ------------------------------------
	Message(EMSG_KEYBOARD),
	key(key),
	x(x),
	y(y),
	down(down)
{

}
