// ****************************************************************************
// genericEnemy.cpp
//
//
// ****************************************************************************

#include "genericEnemy.h"
#include "eAttribute.h"
#include "eComponent.h"

// ------------------------------------
GenericEnemy:: GenericEnemy()
// ------------------------------------
{
	AddAttribute(new SpatialAttr(0, 0));
	AddAttribute(new PhysicAttr());
	AddAttribute(new GeomAttr(GEOM_SQUARE));
	AddAttribute(new HPAttr(100));
	AddAttribute(new DropsAttr());
	AddAttribute(new ColorAttr(COLOR_BLUE));
	AddAttribute(new TexAttr((char*)"BluBlob.png"));
	AddAttribute(new StateAttr());
	
	AddComponent(ECOMP_RENDER);
	AddComponent(ECOMP_PHYSIC);
	AddComponent(ECOMP_COLLISION);
	AddComponent(ECOMP_DAMAGEABLE);
	AddComponent(ECOMP_DROPS);
	AddComponent(ECOMP_SLIME_AI);
}

// ------------------------------------
GenericEnemy::GenericEnemy(float x, float y)
// ------------------------------------
{
	AddAttribute(new SpatialAttr(x, y));
	AddAttribute(new PhysicAttr());
	AddAttribute(new GeomAttr(GEOM_SQUARE));
	AddAttribute(new HPAttr(100));
	AddAttribute(new DropsAttr());
	AddAttribute(new ColorAttr(COLOR_BLUE));
	AddAttribute(new TexAttr((char*)"BluBlob.png"));
	AddAttribute(new StateAttr());
	
	AddComponent(ECOMP_RENDER);
	AddComponent(ECOMP_PHYSIC);
	AddComponent(ECOMP_COLLISION);
	AddComponent(ECOMP_DAMAGEABLE);
	AddComponent(ECOMP_DROPS);
	AddComponent(ECOMP_SLIME_AI);
}

// ------------------------------------
int GenericEnemy::RespondsTo(EMSG m)
// ------------------------------------
{
	if (m == EMSG_RENDER || 
		m == EMSG_THINK ||
		m == EMSG_PHYSIC ||
		m == EMSG_SPATIAL ||
		m == EMSG_COLLISION ||
		m == EMSG_STATE)
		return true;
	return false;
}