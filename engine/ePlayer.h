// ****************************************************************************
// ePlayer.h
//
//
// ****************************************************************************

#ifndef __EPLAYER_H__
#define __EPLAYER_H__

#include "eAbstractObject.h"

class Player : public AbstractObject
{
public:
	Player();
	
	virtual int RespondsTo(EMSG m);
	virtual void HandleMsg(Message* m);
	
	int MovingLeft;
	int MovingRight;
	int MovingUp;
	int MovingDown;
};

#endif
