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