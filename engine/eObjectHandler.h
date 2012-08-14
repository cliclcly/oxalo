// ****************************************************************************
// eObjectHandler.h
// 
// 
// ****************************************************************************

#ifndef __EOBJECTHANDLER_H__
#define __EOBJECTHANDLER_H__


#include <GL/gl.h>

//#include "eEngineClass.h"
//#include "eMessage.h"
//#include "eAbstractObject.h"
#include "eAbstractKeyboardHandler.h"
#include "eScalingBackgroundObject.h"
#include "eTextObject.h"
#include <vector>

class Message;
class AbstractObject;

typedef std::pair<AbstractObject* , AbstractObject* > objpair;

class ObjectHandler
// ------------------------------------
{
public:
	virtual int AddObject(AbstractObject* object) = 0;
	virtual int RemoveObject(AbstractObject* object) = 0;
	virtual int RemoveObject(int GUID) = 0;
	virtual void SendMessage(Message* m) = 0;
	virtual AbstractObject* GetObjectFromGUID(int GUID) = 0;
	
	virtual void FindCollisions(float diff) = 0;
	virtual std::vector<AbstractObject* > GetCollidableObjects() = 0;
	virtual std::vector<objpair > CollisionBroadPhase(float diff) = 0;
	virtual void CollisionNarrowPhase(float diff, std::vector<objpair > objs) = 0;
};

// ------------------------------------
class DumbObjectHandler : public ObjectHandler, public AbstractKeyboardHandler
// ------------------------------------
{
public:
	DumbObjectHandler();

	// ObjectHandler
	virtual int AddObject(AbstractObject* object);
	virtual int RemoveObject(AbstractObject* object);
	virtual int RemoveObject(int GUID);
	virtual void SendMessage(Message* m);
	virtual AbstractObject* GetObjectFromGUID(int GUID);
	
	virtual void FindCollisions(float diff);
	virtual std::vector<AbstractObject* > GetCollidableObjects();
	virtual std::vector<objpair > CollisionBroadPhase(float diff);
	virtual void CollisionNarrowPhase(float diff, std::vector<objpair > objs);
	
	// KeyboardHandler
	virtual void KeyDown(GLubyte key, int x, int y);
	virtual void KeyUp(GLubyte key, int x, int y);
	
	AbstractObject* GetNextObject(AbstractObject* object);
	
private:
	std::vector<AbstractObject* > m_objects;
	AbstractObject* m_current;
};

// ------------------------------------
class TextObjectHandler
// ------------------------------------
{
public:
	virtual int AddTextObject(TextObject* object)=0;
	virtual int RemoveTextObject(TextObject* object)=0;
	virtual void Render()=0;
};


class RelativeTextObjectHandler : public TextObjectHandler
{
public:
	RelativeTextObjectHandler();
	virtual int AddTextObject(TextObject* object);
	virtual int RemoveTextObject(TextObject* object);
	virtual void Render();
	TextObject* GetNextObject(TextObject* object);
	
private:
	std::vector<TextObject* > m_textObjects;
	TextObject* m_current;
};

// ------------------------------------
class StaticTextObjectHandler : public TextObjectHandler
// ------------------------------------
{
public:
	StaticTextObjectHandler();
	virtual int AddTextObject(TextObject* object);
	virtual int RemoveTextObject(TextObject* object);
	virtual void Render();
	
	TextObject* GetNextObject(TextObject* object);
	
private:
	std::vector<TextObject* > m_textObjects;
	TextObject* m_current;
};

// ------------------------------------
class BackgroundObjectHandler : public ObjectHandler
// ------------------------------------
{
public:
	BackgroundObjectHandler();
	virtual int AddBackgroundObject(AbstractObject* object);
	virtual int RemoveBackgroundObject(AbstractObject* object);
	virtual void SendMessage(Message* m);
	
	AbstractObject* GetNextObject(AbstractObject* object);
	
private:
	std::vector<ScalingBackgroundObject* > m_backScaleObjects;
	std::vector<AbstractObject* > m_backObjects;
	TextObject* m_current;
};

#endif
