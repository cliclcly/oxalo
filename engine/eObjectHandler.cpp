// ****************************************************************************
// eObjectHandler.cpp
//
//
// ****************************************************************************

#include "eObjectHandler.h"

#include "eEngineClass.h"
#include <stdio.h>

// ------------------------------------
DumbObjectHandler::DumbObjectHandler()
// ------------------------------------
{

}

// ------------------------------------
int DumbObjectHandler::AddObject(AbstractObject* object)
// ------------------------------------
{
	if (object)
	{
		m_objects.push_back(object);
		return true;
	}
	return false;
}

// ------------------------------------
int DumbObjectHandler::RemoveObject(AbstractObject* object)
// ------------------------------------
{
	std::vector<AbstractObject* >::iterator iter;
	for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		if ((*iter) == object)
			m_objects.erase(iter);
	}
}

// ------------------------------------
int DumbObjectHandler::RemoveObject(int GUID)
// ------------------------------------
{
	std::vector<AbstractObject* >::iterator iter;
	for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		if ((*iter)->GUID == GUID)
			m_objects.erase(iter);
	}
}

// ------------------------------------
void DumbObjectHandler::SendMessage(Message* m)
// ------------------------------------
{
	std::vector<AbstractObject* >::iterator iter;
	for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		(*iter)->HandleMsg(m);
	}
	
	delete m;
}

// ------------------------------------
AbstractObject* DumbObjectHandler::GetObjectFromGUID(int GUID)
// ------------------------------------
{
	std::vector<AbstractObject* >::iterator iter;
	for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		if ((*iter)->GUID == GUID)
			return (*iter);
	}
}

// ------------------------------------
void DumbObjectHandler::FindCollisions(float diff)
// ------------------------------------
{
	std::vector<AbstractObject* >::iterator inner;
	std::vector<AbstractObject* >::iterator outer;
	
	for (outer = m_objects.begin(); outer != m_objects.end(); outer++)
	{
		AbstractObject* o1 = *outer;
		if (!o1->RespondsTo(EMSG_COLLISION))
			continue;
		
		CollisionComponent* cc = 
			static_cast<CollisionComponent* >(o1->GetComponent(ECOMP_COLLISION));
		if (!cc) continue;
		
		CollisionInfo* info1 = cc->GetCollisionInfo();
		
		// Send CollisionMessage to all objects
		for (inner = m_objects.begin(); inner != m_objects.end(); inner++)
		{
			AbstractObject* o2 = *inner;
			if (!o2->RespondsTo(EMSG_COLLISION))
				continue;
				
			CollisionComponent* cc2 = 
				static_cast<CollisionComponent* >(o2->GetComponent(ECOMP_COLLISION));
			if (!cc2) continue;
			
			CollisionInfo* info2 = cc2->GetCollisionInfo();
				
			CollisionMessage* cm1 = new CollisionMessage(diff, info1);
			CollisionMessage* cm2 = new CollisionMessage(diff, info2);
			o2->HandleMsg(cm1);
			o1->HandleMsg(cm2);
			delete cm1;
			delete cm2;
		}
	}
}

// ------------------------------------
void DumbObjectHandler::KeyDown(GLubyte key, int x, int y)
// ------------------------------------
{
	m_keys[key] = 1;
	if (key == 'q')
	{
		AbstractObject* o = GetNextObject(m_current);
		if (o && o->RespondsTo(EMSG_CAMERABLE))
		{
			Camerable* c = static_cast<Camerable* >(static_cast<Square* >(o));
			EngineClass::Instance()->SetCamera(c->GetCamera());
			m_current = o;
		}
	}
}

// ------------------------------------
void DumbObjectHandler::KeyUp(GLubyte key, int x, int y)
// ------------------------------------
{
	m_keys[key] = 0;
}

// ------------------------------------
AbstractObject* DumbObjectHandler::GetNextObject(AbstractObject* object)
// ------------------------------------
{
	std::vector<AbstractObject* >::iterator iter;
	for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		if ((*iter) == object)
		{
			iter++;
			if (iter != m_objects.end())
				return (*iter);
			return (*m_objects.begin());
		}
	}
	return (*m_objects.begin());
}
