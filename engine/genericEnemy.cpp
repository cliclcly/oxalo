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
	AddAttribute(new DropAttr());
	AddAttribute(new ColorAttr(COLOR_BLUE));
	AddAttribute(new TexAttr(std::string("slime"),COLOR_BLUE));
	AddAttribute(new StateAttr());
	AddAttribute(new TypeAttr(std::string("slime")));
	
	AddComponent(ECOMP_RENDER);
	AddComponent(ECOMP_PHYSIC);
	AddComponent(ECOMP_COLLISION);
	AddComponent(ECOMP_DAMAGEABLE);
	AddComponent(ECOMP_DROP);
	AddComponent(ECOMP_SLIME_AI);
	AddComponent(ECOMP_ANIM);
}

// ------------------------------------
GenericEnemy::GenericEnemy(float x, float y)
// ------------------------------------
{
	AddAttribute(new SpatialAttr(x, y));
	AddAttribute(new PhysicAttr());
	AddAttribute(new GeomAttr(GEOM_SQUARE));
	AddAttribute(new HPAttr(100));
	AddAttribute(new DropAttr());
	AddAttribute(new ColorAttr(COLOR_BLUE));
	AddAttribute(new TexAttr(std::string("slime"),COLOR_BLUE));
	AddAttribute(new StateAttr());
	AddAttribute(new TypeAttr(std::string("slime")));
	
	AddComponent(ECOMP_RENDER);
	AddComponent(ECOMP_PHYSIC);
	AddComponent(ECOMP_COLLISION);
	AddComponent(ECOMP_DAMAGEABLE);
	AddComponent(ECOMP_DROP);
	AddComponent(ECOMP_SLIME_AI);
	AddComponent(ECOMP_ANIM);
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
		m == EMSG_STATE ||
		m == EMSG_DROP ||
		m == EMSG_DIE ||
		m == EMSG_KEYBOARD ||
		m == EMSG_DAMAGE
		)
		return true;
	return false;
}

// ------------------------------------
void GenericEnemy::HandleMsg(Message* m)
// ------------------------------------
{
	if (m->type == EMSG_KEYBOARD)
	{
		KeyboardMessage* km = static_cast<KeyboardMessage* >(m);
		if (km->key == 'p')
		{
			this->HandleMsg(new DamageMessage(100));
		}
	}
	AbstractObject::HandleMsg(m);
}