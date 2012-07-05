// ****************************************************************************
// ePlatform.h
// 
//
// ****************************************************************************

#ifndef __EPLATFORM_H__
#define __EPLATFORM_H__

#include "eAbstractObject.h"
#include "ePolygon.h"

class Platform : public AbstractObject
{
public:
	Platform();
	Platform(Vector2 base, Vector2 width);
	
	virtual int RespondsTo(EMSG );
	
private:
	Vector2 _base;
	Vector2 _dim;
};

#endif
