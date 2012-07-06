// ****************************************************************************
// eComponent.cpp
//
//
// ****************************************************************************

#include "eComponent.h"
#include "eAbstractObject.h"
#include "eDebug.h"

#include <windows.h>
#include <GL/glut.h>
#include <IL/ilut.h>

#include <math.h>

#include <stdio.h>

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
	if (c == ECOMP_RENDER)
		return new RenderComponent();
	if (c == ECOMP_PHYSIC)
		return new PhysicComponent();
	if (c == ECOMP_COLLISION)
		return new CollisionComponent();
	if (c == ECOMP_DAMAGEABLE)
		return new DamageableComponent();
	if (c == ECOMP_DROPS)
		return new DropsComponent();
	if (c == ECOMP_HUD_HP)
		return new HP_HUDComponent();
}

// ------------------------------------
void Component::SetAttribute(Attribute* ar)
// ------------------------------------
{
	if (type == ECOMP_RENDER)
	{
		RenderComponent* rc = static_cast<RenderComponent* >(this);
		if (ar->type == EATTR_SPATIAL)
			rc->m_spatial = static_cast<SpatialAttr* >(ar);
		if (ar->type == EATTR_GEOM)
			rc->m_geom = static_cast<GeomAttr* >(ar);
		if (ar->type == EATTR_TEXTURE)
			rc->m_tex = static_cast<TexAttr* >(ar);
	}
	if (type == ECOMP_PHYSIC)
	{
		PhysicComponent* pc = static_cast<PhysicComponent* >(this);
		if (ar->type == EATTR_SPATIAL)
			pc->m_spatial = static_cast<SpatialAttr* >(ar);
		if (ar->type == EATTR_PHYSIC)
			pc->m_physic = static_cast<PhysicAttr* >(ar);
		if (ar->type == EATTR_STATE)
			pc->m_state = static_cast<StateAttr* >(ar);
	}
	if (type == ECOMP_COLLISION)
	{
		CollisionComponent* cc = static_cast<CollisionComponent* >(this);
		if (ar->type == EATTR_SPATIAL)
			cc->m_spatial = static_cast<SpatialAttr* >(ar);
		if (ar->type == EATTR_GEOM)
			cc->m_geom = static_cast<GeomAttr* >(ar);
	}
	if (type == ECOMP_DAMAGEABLE)
	{
		DamageableComponent* dac = static_cast<DamageableComponent* >(this);
		if (ar->type == EATTR_HP)
			dac->m_hp = static_cast<HPAttr* >(ar);
	}
	if (type == ECOMP_DROPS)
	{
		DropsComponent* dec = static_cast<DropsComponent* >(this);
		if (ar->type == EATTR_DROPS)
			dec->m_drops = static_cast<DropsAttr* >(ar);
	}
	if (type == ECOMP_HUD_HP)
	{
		HP_HUDComponent* hp = 
			static_cast<HP_HUDComponent* >(this);
		if (ar->type == EATTR_HP)
			hp->m_hp = static_cast<HPAttr* >(ar);
	}
	if (type == ECOMP_AI)
	{
	
	}
}

// ------------------------------------
RenderComponent::RenderComponent() :
// ------------------------------------
	Component(ECOMP_RENDER),
	m_spatial(0),
	m_geom(0),
	m_tex(0)
{
	reqs.push_back(EATTR_SPATIAL);
	reqs.push_back(EATTR_GEOM);
	reqs.push_back(EATTR_TEXTURE);
}

// ------------------------------------
void RenderComponent::HandleMsg(Message* m)
// ------------------------------------
{
	if (m->type == EMSG_RENDER)
	{
		GLuint texture = m_tex->GetTexture();
		glBindTexture(GL_TEXTURE_2D,texture);
		switch(m_geom->m_shape)
		{
			case GEOM_SQUARE:
			{
				glPushMatrix();	
				glTranslatef(m_spatial->pos.x, m_spatial->pos.y, 0);
				//glColor4f(1.0, 0.0, 0.0, 1.0);
				
				Box* b = m_geom->m_bound;
				
				glBegin(GL_QUADS);
					glTexCoord2f(0, 0);
					glVertex2f(b->base.x, b->base.y);
					glTexCoord2f(0, 1);
					glVertex2f(b->base.x, b->base.y + b->dim.y);
					glTexCoord2f(1, 1);
					glVertex2f(b->base.x + b->dim.x, b->base.y + b->dim.y);
					glTexCoord2f(1, 0);
					glVertex2f(b->base.x + b->dim.x, b->base.y);
				glEnd();
				
				glPopMatrix();
				break;
			}
			case GEOM_TRIANGLE:
				glPushMatrix();	
				glTranslatef(m_spatial->pos.x, m_spatial->pos.y, 0);
				//glColor4f(1.0, 0.0, 0.0, 1.0);
				
				glBegin(GL_TRIANGLES);
					glTexCoord2f(.5, 1);
					glVertex2f(0,.5);
					glTexCoord2f(0, 0);
					glVertex2f(.5,-.5);
					glTexCoord2f(1, 0);
					glVertex2f(-.5,-.5);
				glEnd();
				
				glPopMatrix();
				break;
		}
		glBindTexture(GL_TEXTURE_2D,0);
	}
}

// ------------------------------------
PhysicComponent::PhysicComponent() :
// ------------------------------------
	Component(ECOMP_PHYSIC)
{
	reqs.push_back(EATTR_SPATIAL);
	reqs.push_back(EATTR_PHYSIC);
	reqs.push_back(EATTR_STATE);
}

// ------------------------------------
void PhysicComponent::HandleMsg(Message* m)
// ------------------------------------
{
	if (m->type == EMSG_THINK)
	{
		ThinkMessage* tm = static_cast<ThinkMessage* >(m);
		
		m_physic->lastpos = m_spatial->pos;
		
		if (parent->RespondsTo(EMSG_STATE))
		{
			StateAttr* state = 
				static_cast<StateAttr* >(parent->GetAttribute(EATTR_STATE));
				
			if (m_physic->vel.y <= 0.1 && m_physic->vel.y >= -0.1)
			{
				state->jumping = false;
			}
			
			if (state->falling == true || state->jumping)
				m_physic->vel.y = m_physic->lastvel.y;
			else if (!state->jumping)
				state->falling = true;
		}
		
		m_spatial->pos += m_physic->vel.scale(tm->m_diff);
		m_physic->vel = m_physic->vel + Vector2(0, -10 * tm->m_diff);
		
		if (parent->RespondsTo(EMSG_STATE))
		{
			StateAttr* state = 
				static_cast<StateAttr* >(parent->GetAttribute(EATTR_STATE));
			state->falling = true;
		}
		
		m_physic->lastvel = m_physic->vel;
	}
}

// ------------------------------------
CollisionInfo::CollisionInfo() :
// ------------------------------------
	other(0),
	pos(Vector2(0, 0)),
	vel(Vector2(0, 0)),
	bound(0)
{
	
}

// ------------------------------------
CollisionComponent::CollisionComponent() :
// ------------------------------------
	Component(ECOMP_COLLISION),
	m_info(0)
{
	reqs.push_back(EATTR_SPATIAL);
	reqs.push_back(EATTR_GEOM);
}

// ------------------------------------
void CollisionComponent::HandleMsg(Message* m)
// ------------------------------------
{
	switch(m->type)
	{
	case EMSG_COLLISION:
		CollisionMessage* cm = static_cast<CollisionMessage* >(m);
		CollisionInfo* info = cm->info;
		
		// break if colliding objects are same object
		if (parent->GUID == info->other->GUID)
			break;
		
		// generate AABBs
		Box* mybox = m_geom->m_bound;
		Box* itsbox = info->bound;
		
		Box* mytr = mybox->Translate(m_spatial->pos.x, m_spatial->pos.y);
		Box* itstr = itsbox->Translate(info->pos.x, info->pos.y);
		
		
		if (mytr->IsColliding(itstr))
		{			
			// find corner that is colliding
			Vector2 point;
			Vector2 offset = Vector2(0, 0);
			if (itstr->Contains(mytr->base))
				offset = mytr->base - m_spatial->pos;
			else if (itstr->Contains(mytr->base + Vector2(mytr->dim.x, 0)))
				offset = mytr->base + Vector2(mytr->dim.x, 0) - m_spatial->pos;
			else if (itstr->Contains(mytr->base + Vector2(0, mytr->dim.y)))
				offset = mytr->base + Vector2(0, mytr->dim.y) - m_spatial->pos;
			else if (itstr->Contains(mytr->base + mytr->dim))
				offset = mytr->base + mytr->dim - m_spatial->pos;
		
			SpatialAttr* itsSA = 
				static_cast<SpatialAttr* >(info->other->GetAttribute(EATTR_SPATIAL));
			SpatialAttr* mySA = 
				static_cast<SpatialAttr* >(parent->GetAttribute(EATTR_SPATIAL));	

			// prevent gondola-ing
			if (info->other->RespondsTo(EMSG_PHYSIC))
			{
				PhysicAttr* pa = 
					static_cast<PhysicAttr* >(info->other->GetAttribute(EATTR_PHYSIC));
				itsSA->pos = pa->lastpos;
				pa->vel = Vector2(0, 0);
			}
			
			// resolve collision
			if (parent->RespondsTo(EMSG_PHYSIC))
			{
				PhysicAttr* pa = 
					static_cast<PhysicAttr* >(parent->GetAttribute(EATTR_PHYSIC));
					
				Vector2 vel = pa->vel;
				Vector2 impact = itstr->IntersectionPoint(Ray2(pa->lastpos + offset, vel));
				Vector2 pene = m_spatial->pos + offset - impact;
				
				if (impact.x == 0 && impact.y == 0) break;
				
				point = m_spatial->pos;
				Vector2 oldvel = pa->vel;
				
						
				if (pene.length() > 0)
				{
					Vector2 n = itstr->NormalHitBy(pa->lastpos + offset, vel);
					Vector2 pn = pene.project(n);
					Vector2 newpos = pene - pn.scale(2);
					//mySA->pos += (pn.scale(-2) - pn.normalize().scale(0.001));
					mySA->pos += (pn.scale(-2));
					
					pn = vel.project(n);
					Vector2 newvel = vel - pn.scale(2);
					pa->vel = newvel.scale(0.001);
					
					// update state
					if (parent->RespondsTo(EMSG_STATE))
					{
						StateAttr* state = 
							static_cast<StateAttr* >(parent->GetAttribute(EATTR_STATE));
							
						// cancel falling	
						float angle = atan2(n.y, n.x);
						if (angle >= 60 * 3.14159 / 180 && angle <= 120 * 3.14159 / 180)
						{
							state->jumped = false;
							state->falling = false;
						}
						
						// cancel jumping up into things
						if (angle >= -120 * 3.14159 / 180 && angle <= -60 * 3.14159 / 180)
						{
							state->jumping = false;
							state->falling = false;
						}
					}
					
					// debug information
					/*
					if (newpos.length() > 0)
					{					
						printf("MyBase: %f, %f\n", mytr->base.x, mytr->base.y);
						printf("MyDim: %f, %f\n", mytr->dim.x, mytr->dim.y);
						printf("ItsBase: %f, %f\n", itstr->base.x, itstr->base.y);
						printf("ItsDim: %f, %f\n", itstr->dim.x, itstr->dim.y);
						printf("LastPos: "); (pa->lastpos + offset).print();
						printf("\nPoint: "); (point + offset).print();
						printf("\nNormal: "); n.print();
						printf("\nPene: "); pene.print();
						printf("\nOffset: "); offset.print();
						printf("\nVel: "); oldvel.print(); 
						printf("\nImpact: "); impact.print();
						printf("\nNewpos: "); (mySA->pos + offset).print();
						printf("\n\n");
					}
					*/
				}
				
			}
		}
		
		delete mytr;
		delete itstr;
		
		break;
	}
}

// ------------------------------------
CollisionInfo* CollisionComponent::GetCollisionInfo()
// ------------------------------------
{
	if (m_info)
	{
		// update pos, vel
		if (parent->RespondsTo(EMSG_PHYSIC))
		{
			PhysicAttr* pa = 
				static_cast<PhysicAttr* >(parent->GetAttribute(EATTR_PHYSIC));
			m_info->vel = pa->vel;
			SpatialAttr* sa = 
				static_cast<SpatialAttr* >(parent->GetAttribute(EATTR_SPATIAL));
			m_info->pos = sa->pos;
		}
		return m_info;
	}
	else
	{
	
		CollisionInfo* info = new CollisionInfo();
		info->other = parent;
		
		if (parent->RespondsTo(EMSG_PHYSIC))
		{
			PhysicAttr* pa = 
				static_cast<PhysicAttr* >(parent->GetAttribute(EATTR_PHYSIC));
			info->vel = pa->vel;
		}
		else
		{
			info->vel = Vector2(0, 0);
		}
		
		SpatialAttr* sa = 
			static_cast<SpatialAttr* >(parent->GetAttribute(EATTR_SPATIAL));
		info->pos = sa->pos;
		
		GeomAttr* ga =
			static_cast<GeomAttr* >(parent->GetAttribute(EATTR_GEOM));
		info->bound = ga->m_bound;
		
		m_info = info;
		return info;
	}
}

// ------------------------------------
DamageableComponent::DamageableComponent() :
// ------------------------------------
	Component(ECOMP_DAMAGEABLE)
{
	reqs.push_back(EATTR_HP);
}

// ------------------------------------
void DamageableComponent::HandleMsg(Message* m)
// ------------------------------------
{
	switch(m->type)
	{
	case EMSG_DAMAGE:
		DamageMessage* cm = static_cast<DamageMessage* >(m);
		HPAttr* hpa = 
				static_cast<HPAttr* >(parent->GetAttribute(EATTR_HP));
		if (hpa->currentHP-cm->damage<=0)
		{
			hpa->currentHP=0;
			//kill
		}
		hpa->currentHP-=cm->damage;
	break;
	}
}

// ------------------------------------
DropsComponent::DropsComponent() :
// ------------------------------------
	Component(ECOMP_DROPS)
{
	reqs.push_back(EATTR_DROPS);
}

// ------------------------------------
void DropsComponent::HandleMsg(Message* m)
// ------------------------------------
{
	switch(m->type)
	{
	case EMSG_DROP:
	break;
	}
}

// ------------------------------------
AIComponent::AIComponent() :
// ------------------------------------
	Component(ECOMP_AI)
{
}

// ------------------------------------
void AIComponent::HandleMsg(Message* m)
// ------------------------------------
{

}

// ------------------------------------
HP_HUDComponent::HP_HUDComponent() :
// ------------------------------------
	Component(ECOMP_HUD_HP)
{
	reqs.push_back(EATTR_HP);
}

// ------------------------------------
void HP_HUDComponent::HandleMsg(Message* m)
// ------------------------------------
{
	float pHealth = (float) m_hp->currentHP / (float) m_hp->maxHP;
	if (m->type == EMSG_RENDER_HUD)
	{
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glBegin(GL_QUADS);
			glVertex2f(0.05, 0.05);
			glVertex2f(0.05, 0.10);
			glVertex2f(0.45, 0.10);
			glVertex2f(0.45, 0.05);
		glEnd();
		glColor4f(1.0, 1.0, 1.0, 1.0);
	}
}
