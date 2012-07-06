// ****************************************************************************
// ePlayer.cpp
//
//
// ****************************************************************************

#include "ePlayer.h"
#include <stdio.h>
#include "eDebug.h"

// ------------------------------------
Player::Player() : 
// ------------------------------------
	MovingLeft(false),
	MovingRight(false),
	MovingUp(false),
	MovingDown(false),
	speed(5),
	jumpPower(7)
{
	AddAttribute(new SpatialAttr(12, 12));
	AddAttribute(new GeomAttr(GEOM_SQUARE));
	AddAttribute(new PhysicAttr());
	AddAttribute(new StateAttr());
	AddAttribute(new HPAttr());
	
	AddComponent(ECOMP_RENDER);
	AddComponent(ECOMP_PHYSIC);
	AddComponent(ECOMP_COLLISION);
	AddComponent(ECOMP_HUD_HP);
}

// ------------------------------------
int Player::RespondsTo(EMSG m)
// ------------------------------------
{
	if (m == EMSG_RENDER ||
		m == EMSG_THINK ||
		m == EMSG_COLLISION ||
		m == EMSG_PHYSIC ||
		m == EMSG_KEYBOARD ||
		m == EMSG_SPATIAL ||
		m == EMSG_STATE)
		return true;
	return false;
}

// ------------------------------------
void Player::HandleMsg(Message* m)
// ------------------------------------
{
	//AbstractObject::HandleMsg(m);
	if (m->type == EMSG_KEYBOARD)
	{
		KeyboardMessage* km = static_cast<KeyboardMessage* >(m);
		if (km->key == 'a')
			MovingLeft = km->down;
		if (km->key == 'd')
			MovingRight = km->down;
		if (km->key == 'w')
			MovingUp = km->down;
		if (km->key == 's')
			MovingDown = km->down;
	}
	if (m->type == EMSG_THINK)
	{
		ThinkMessage* tm = static_cast<ThinkMessage* >(m);
		SpatialAttr* sa = static_cast<SpatialAttr* >(GetAttribute(EATTR_SPATIAL));
		PhysicAttr* pa = static_cast<PhysicAttr* >(GetAttribute(EATTR_PHYSIC));
		StateAttr* state = static_cast<StateAttr* >(GetAttribute(EATTR_STATE));
		
		if (tm->tock)
		{
			printf("Vel: ");
			pa->vel.print();
			printf("\nPos: ");
			sa->pos.print();
			printf("\n");
		}
			
		
		if (MovingLeft)
		{
			pa->vel.x = -speed;
		}
		if (MovingRight)
			pa->vel.x = speed;
		if (!MovingLeft && !MovingRight)
			pa->vel.x = 0;
		if (MovingUp)
		{
			if (!state->jumped)
			{
				sa->pos.y += 0.01;
				pa->vel.y = jumpPower;
				pa->lastvel.y = jumpPower;
				MovingUp = false;
				state->jumped = true;
				state->jumping = true;
				state->falling = false;
			}
		}
	}
	
	// having this last is super important for collision for some reason...
	AbstractObject::HandleMsg(m);
}
