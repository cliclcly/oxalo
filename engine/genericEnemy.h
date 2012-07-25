// ****************************************************************************
// genericEnemy.h
//
//
// ****************************************************************************

#ifndef __GENERICENEMY_H__
#define __GENERICENEMY_H__

#include "eAbstractObject.h"

// ------------------------------------
class GenericEnemy :  public AbstractObject
// ------------------------------------
{
public:
	GenericEnemy();
	
	GenericEnemy(float x, float y);
	
	virtual int RespondsTo(EMSG m);
	virtual void HandleMsg(Message* m);
};

#endif