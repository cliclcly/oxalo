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
RenderMessage::RenderMessage(EMSG type) :
// ------------------------------------
	Message(type)
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

// ------------------------------------
DamageMessage::DamageMessage(int damage) :
// ------------------------------------
	Message(EMSG_DAMAGE),
	damage(damage)
{
	
}

// ------------------------------------
DropMessage::DropMessage() :
// ------------------------------------
	Message(EMSG_DROP)
{
	
}

// ------------------------------------
DieMessage::DieMessage() :
// ------------------------------------
	Message(EMSG_DIE)
{
	
}

// ------------------------------------
ChangeAnimMessage::ChangeAnimMessage(ANIM toChange, int startframe) :
// ------------------------------------
	Message(EMSG_CHANGEANIM),
	changeAnim(toChange),
	startFrame(startframe)
{

}