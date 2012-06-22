// ****************************************************************************
// eAbstractKeyboardHandler.h
//
//
// ****************************************************************************

#ifndef __EABSTRACTKEYBOARDHANDLER_H__
#define __EABSTRACTKEYBOARDHANDLER_H__

#include <windows.h>
#include <GL/glut.h>

#include <vector>

class AbstractKeyboardHandler
{
public:
	virtual void KeyDown(GLubyte key, int x, int y) = 0;
	virtual void KeyUp(GLubyte key, int x, int y) = 0;
	
protected:
	GLubyte m_keys[255];
};

class DumbKeyboardHandler : public AbstractKeyboardHandler
{
public:
	DumbKeyboardHandler();
	~DumbKeyboardHandler();
	
	void KeyDown(GLubyte key, int x, int y);
	void KeyUp(GLubyte key, int x, int y);
};

// ------------------------------------
class KeyboardStack
// ------------------------------------
{
public:
	virtual void KeyDown(GLubyte key, int x, int y);
	virtual void KeyUp(GLubyte key, int x, int y);
	
	virtual void PushKeyboardHandler(AbstractKeyboardHandler* );
	virtual void PopKeyboardHandler();
	
private:
	std::vector<AbstractKeyboardHandler* > m_handlers;
};

#endif
