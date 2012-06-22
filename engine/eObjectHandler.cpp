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
