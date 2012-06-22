// ****************************************************************************
// eComponent.cpp
//
//
// ****************************************************************************

#include "eComponent.h"

// ------------------------------------
Component::Component() :
// ------------------------------------
	type(ECOMP_DEFAULT)
{
	
}

// ------------------------------------
Component::Component(ECOMP type) :
// ------------------------------------
	type(type)
{

}

// ------------------------------------
Component* Component::GetNewComponent(ECOMP c)
// ------------------------------------
{
	if (c ==  ECOMP_RENDER)
		return new RenderComponent();
}

// ------------------------------------
RenderComponent::RenderComponent() :
// ------------------------------------
	Component(ECOMP_RENDER)
{
	reqs.push_back(EATTR_SPATIAL);
}

// ------------------------------------
void RenderComponent::HandleMsg(Message* )
// ------------------------------------
{

}
