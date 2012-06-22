// ****************************************************************************
// eComponent.h
//
//
// ****************************************************************************

#ifndef __ECOMPONENT_H__
#define __ECOMPONENT_H__

#include <vector>
#include "eMessage.h"
#include "eAttribute.h"

enum ECOMP
{
	ECOMP_DEFAULT,
	ECOMP_RENDER
};

// ------------------------------------
class Component
// ------------------------------------
{
public:
	Component();
	Component(ECOMP type);
	
	static Component* GetNewComponent(ECOMP c);

	virtual void HandleMsg(Message* ) = 0;
	
	ECOMP type;
	std::vector<EATTR> reqs;
};

// ------------------------------------
class RenderComponent : public Component
// ------------------------------------
{
public:
	RenderComponent();
	
	virtual void HandleMsg(Message* );
	
	SpatialAttr* m_spatial;
};

#endif
