// ****************************************************************************
// eObjectHandler.h
// 
// 
// ****************************************************************************

#ifndef __EOBJECTHANDLER_H__
#define __EOBJECTHANDLER_H__


#include <GL/gl.h>

//#include "eEngineClass.h"
#include "eMessage.h"
#include "eAbstractObject.h"
#include "eAbstractKeyboardHandler.h"
#include <vector>

class ObjectHandler
{
public:
	virtual int AddObject(AbstractObject* object) = 0;
	virtual int RemoveObject(AbstractObject* object) = 0;
	virtual int RemoveObject(int GUID) = 0;
	virtual void SendMessage(Message* m) = 0;
	virtual AbstractObject* GetObjectFromGUID(int GUID) = 0;
};

class DumbObjectHandler : public ObjectHandler, public AbstractKeyboardHandler
{
public:
	DumbObjectHandler();

	// ObjectHandler
	virtual int AddObject(AbstractObject* object);
	virtual int RemoveObject(AbstractObject* object);
	virtual int RemoveObject(int GUID);
	virtual void SendMessage(Message* m);
	virtual AbstractObject* GetObjectFromGUID(int GUID);
	
	// KeyboardHandler
	virtual void KeyDown(GLubyte key, int x, int y);
	virtual void KeyUp(GLubyte key, int x, int y);
	
	AbstractObject* GetNextObject(AbstractObject* object);
	
private:
	std::vector<AbstractObject* > m_objects;
	AbstractObject* m_current;
};

#endif
