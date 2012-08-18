// ****************************************************************************
// eAIs.cpp
//
//
// ****************************************************************************

#include "eAIs.h"
#include "eAbstractObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ------------------------------------
SlimeAIComponent::SlimeAIComponent() : 
// ------------------------------------
	Component(ECOMP_SLIME_AI),
	waitTime(0),
	jumpPower(5),
	movePower(3)
{
	reqs.push_back(EATTR_SPATIAL);
	reqs.push_back(EATTR_PHYSIC);
	reqs.push_back(EATTR_STATE);
}

// ------------------------------------
void SlimeAIComponent::HandleMsg(Message* m)
// ------------------------------------
{
	switch(m->type)
	{
		case EMSG_THINK:
		{
			ThinkMessage* tm = static_cast<ThinkMessage* >(m);
			
			if(!m_state->jumped  && !m_state->jumping && !m_state->falling )
			{
				printf("landed\n");
			}
			if(!m_state->jumped)
			{
				if(waitTime+tm->m_diff>1)
				{
					srand(time(NULL));
					waitTime=0;
					m_spatial->pos.y += 0.01;
					m_physic->vel.y = jumpPower;
					m_physic->vel.y = jumpPower;
					m_physic->lastvel.y = jumpPower;
					m_physic->vel.x = movePower;
					if(rand()%2==1)
					{
						m_physic->vel.x *=-1;
					}
					m_state->jumped = true;
					m_state->jumping = true;
					m_state->falling = false;
					parent->HandleMsg(new ChangeAnimMessage(ANIM_JUMP,0));
				}else{
					parent->HandleMsg(new ChangeAnimMessage(ANIM_STILL,0));	
					m_physic->vel.x = 0;
					waitTime+=tm->m_diff;
				}
			}else{
			}
			
			break;
		}
		default:
			break;
	}
	
}


//------------  MODEL FOR AI ------------

// ------------------------------------
EnemyAIComponent::EnemyAIComponent() : 
// ------------------------------------
	Component(ECOMP_ENEMY_AI)
{

}

// ------------------------------------
void EnemyAIComponent::HandleMsg(Message* m)
// ------------------------------------
{

}