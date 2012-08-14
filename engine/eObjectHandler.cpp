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
		{
			m_objects.erase(iter);
			return true;
		}
	}
	return false;
}

// ------------------------------------
int DumbObjectHandler::RemoveObject(int GUID)
// ------------------------------------
{
	std::vector<AbstractObject* >::iterator iter;
	for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		if ((*iter)->GUID == GUID)
		{
			m_objects.erase(iter);
			return true;
		}
	}
	return false;
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
	/*
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
			
			//CollisionInfo* info2 = cc2->GetCollisionInfo();
				
			CollisionMessage* cm1 = new CollisionMessage(diff, info1);
			//CollisionMessage* cm2 = new CollisionMessage(diff, info2);
			o2->HandleMsg(cm1);
			//o1->HandleMsg(cm2);
			delete cm1;
			//delete cm2;
		}
	}
	*/
	
	std::vector<AbstractObject* > objs = GetCollidableObjects();
	std::vector<objpair > pairs = CollisionBroadPhase(diff);
	CollisionNarrowPhase(diff, pairs);
}

// ------------------------------------
std::vector<AbstractObject* > DumbObjectHandler::GetCollidableObjects()
// ------------------------------------
{
	std::vector<AbstractObject* > objs;
	std::vector<AbstractObject* >::iterator it;
	for (it = m_objects.begin(); it != m_objects.end(); it++)
	{
		AbstractObject* obj = *it;
		if (obj->RespondsTo(EMSG_COLLISION))
			objs.push_back(obj);
	}
	
	return objs;
}

// ------------------------------------
std::vector<objpair > DumbObjectHandler::CollisionBroadPhase(float diff)
// ------------------------------------
{
	std::vector<AbstractObject* > collidables = GetCollidableObjects();
	std::vector<objpair > colliding;
	std::vector<AbstractObject* >::iterator outer;
	std::vector<AbstractObject* >::iterator inner;
	for (outer = collidables.begin(); outer != collidables.end(); outer++)
	{	
		AbstractObject* o1 = *outer;
		CollisionComponent* cc1 = 
			static_cast<CollisionComponent* >(o1->GetComponent(ECOMP_COLLISION));
		
		//for (inner = collidables.begin(); inner != collidables.end(); inner++)
		for (inner = outer; inner != collidables.end(); inner++)
		{
			if (*outer == *inner) continue;
			
			AbstractObject* o2 = *inner;
			CollisionComponent* cc2 = 
				static_cast<CollisionComponent* >(o2->GetComponent(ECOMP_COLLISION));
			
			Box b1 = cc1->GetAABB();
			Box b2 = cc2->GetAABB();
			
			if (b1.IsColliding(b2))
			{
				objpair p = std::make_pair(o1, o2);
				colliding.push_back(p);
			}
		}
	}
	
	return colliding;
}

// ------------------------------------
void DumbObjectHandler::CollisionNarrowPhase(float diff, std::vector<objpair > objs)
// ------------------------------------
{
	std::vector<objpair >::iterator it;
	for (it = objs.begin(); it != objs.end(); it++)
	{
		AbstractObject* o1 = (*it).first;
		AbstractObject* o2 = (*it).second;
		CollisionComponent* cc1 = 
			static_cast<CollisionComponent* >(o1->GetComponent(ECOMP_COLLISION));
		CollisionComponent* cc2 = 
			static_cast<CollisionComponent* >(o2->GetComponent(ECOMP_COLLISION));
			
		Mesh m1 = cc1->GetMesh();
		Mesh m2 = cc2->GetMesh();
		//printf("m1: "); m1.Print();
		//printf("m2: "); m2.Print();
		
		int colliding = m1.GJK(m2);
		if (colliding)
		{
			std::pair<float, Vector2> pen = m1.EPA(m2);
			
			Vector2 v1 = cc1->GetVelocity();
			Vector2 v2 = cc2->GetVelocity();
			
			//float j = v1.length() + v2.length();
			float j = -1.2 * (v2 - v1).dot(pen.second);
			/*
			if (j != 0)
			{
				printf("DOH: j: %f\n", j);
				printf("GUID o1: %d\n", o1->GUID);
				printf("GUID o2: %d\n", o2->GUID);
			}
			*/
				
			if (j > 0) 
			{
				cc2->ApplyImpulse(pen.second, j);
				cc1->ApplyImpulse(pen.second, -j);
			}
		}
	}
}

// ------------------------------------
void DumbObjectHandler::KeyDown(GLubyte key, int x, int y)
// ------------------------------------
{
	m_keys[key] = 1;
	
	KeyboardMessage* km = new KeyboardMessage(key, x, y, 1);
	
	std::vector<AbstractObject* >::iterator it;
	for (it = m_objects.begin(); it != m_objects.end(); it++)
	{
		if ((*it)->RespondsTo(EMSG_KEYBOARD))
		{
			(*it)->HandleMsg(km);
		}
	}
	
	delete km;
}

// ------------------------------------
void DumbObjectHandler::KeyUp(GLubyte key, int x, int y)
// ------------------------------------
{
	m_keys[key] = 0;
	
	KeyboardMessage* km = new KeyboardMessage(key, x, y, 0);
	
	std::vector<AbstractObject* >::iterator it;
	for (it = m_objects.begin(); it != m_objects.end(); it++)
	{
		if ((*it)->RespondsTo(EMSG_KEYBOARD))
		{
			(*it)->HandleMsg(km);
		}
	}
	
	delete km;
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

// ------------------------------------
RelativeTextObjectHandler::RelativeTextObjectHandler()
// ------------------------------------
{

}

// ------------------------------------
int RelativeTextObjectHandler::AddTextObject(TextObject* object)
// ------------------------------------
{
	if (object)
	{
		m_textObjects.push_back(object);
		return true;
	}
	return false;
}

// ------------------------------------
int RelativeTextObjectHandler::RemoveTextObject(TextObject* object)
// ------------------------------------
{
	std::vector<TextObject* >::iterator iter;
	for (iter = m_textObjects.begin(); iter != m_textObjects.end(); iter++)
	{
		if ((*iter) == object)
		{
			m_textObjects.erase(iter);
			return true;
		}
	}
	return false;
}


// ------------------------------------
void RelativeTextObjectHandler::Render()
// ------------------------------------
{
	std::vector<TextObject* >::iterator iter;
	for (iter = m_textObjects.begin(); iter != m_textObjects.end(); iter++)
	{
		(*iter)->render();
	}
}

// ------------------------------------
TextObject * RelativeTextObjectHandler::GetNextObject(TextObject* object)
// ------------------------------------
{
	std::vector<TextObject* >::iterator iter;
	for (iter = m_textObjects.begin(); iter != m_textObjects.end(); iter++)
	{
		if ((*iter) == object)
		{
			iter++;
			if (iter != m_textObjects.end())
				return (*iter);
			return (*m_textObjects.begin());
		}
	}
	return (*m_textObjects.begin());
}

// ------------------------------------
StaticTextObjectHandler::StaticTextObjectHandler()
// ------------------------------------
{

}

// ------------------------------------
int StaticTextObjectHandler::AddTextObject(TextObject* object)
// ------------------------------------
{
	if (object)
	{
		m_textObjects.push_back(object);
		return true;
	}
	return false;
}

// ------------------------------------
int StaticTextObjectHandler::RemoveTextObject(TextObject* object)
// ------------------------------------
{
	std::vector<TextObject* >::iterator iter;
	for (iter = m_textObjects.begin(); iter != m_textObjects.end(); iter++)
	{
		if ((*iter) == object)
		{
			m_textObjects.erase(iter);
			return true;
		}
	}
	return false;
}


// ------------------------------------
void StaticTextObjectHandler::Render()
// ------------------------------------
{
	std::vector<TextObject* >::iterator iter;
	for (iter = m_textObjects.begin(); iter != m_textObjects.end(); iter++)
	{
		(*iter)->render();
	}
}

// ------------------------------------
TextObject * StaticTextObjectHandler::GetNextObject(TextObject* object)
// ------------------------------------
{
	std::vector<TextObject* >::iterator iter;
	for (iter = m_textObjects.begin(); iter != m_textObjects.end(); iter++)
	{
		if ((*iter) == object)
		{
			iter++;
			if (iter != m_textObjects.end())
				return (*iter);
			return (*m_textObjects.begin());
		}
	}
	return (*m_textObjects.begin());
}

// ------------------------------------
BackgroundObjectHandler::BackgroundObjectHandler()
// ------------------------------------
{

}

// ------------------------------------
int BackgroundObjectHandler::AddBackgroundObject(AbstractObject* object)
// ------------------------------------
{
	if (object)
	{
		m_backObjects.push_back(object);
		return true;
	}
	return false;
}

// ------------------------------------
int BackgroundObjectHandler::RemoveBackgroundObject(AbstractObject* object)
// ------------------------------------
{
	std::vector<AbstractObject* >::iterator iter;
	for (iter = m_backObjects.begin(); iter != m_backObjects.end(); iter++)
	{
		if ((*iter) == object)
		{
			m_backObjects.erase(iter);
			return true;
		}
	}
	return false;
}

// ------------------------------------
void BackgroundObjectHandler::SendMessage(Message* m)
// ------------------------------------
{
	std::vector<ScalingBackgroundObject*>::iterator iter1;
	for (iter1 = m_backScaleObjects.begin(); iter1 != m_backScaleObjects.end(); iter1++)
	{
		(*iter1)->HandleMsg(m);
	}
	
	std::vector<AbstractObject* >::iterator iter2;
	for (iter2 = m_backObjects.begin(); iter2 != m_backObjects.end(); iter2++)
	{
		(*iter2)->HandleMsg(m);
	}
	
	delete m;
}

// ------------------------------------
AbstractObject* BackgroundObjectHandler::GetNextObject(AbstractObject* object)
// ------------------------------------
{
	std::vector<AbstractObject* >::iterator iter;
	for (iter = m_backObjects.begin(); iter != m_backObjects.end(); iter++)
	{
		if ((*iter) == object)
		{
			iter++;
			if (iter != m_backObjects.end())
				return (*iter);
			return (*m_backObjects.begin());
		}
	}
	return (*m_backObjects.begin());
}
