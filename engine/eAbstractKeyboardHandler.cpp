// ****************************************************************************
// eAbstractKeyboardHandler.cpp
//
//
// ****************************************************************************

#include "eAbstractKeyboardHandler.h"

#include <stdio.h>

// ------------------------------------
DumbKeyboardHandler::DumbKeyboardHandler()
// ------------------------------------
{

}

// ------------------------------------
DumbKeyboardHandler::~DumbKeyboardHandler()
// ------------------------------------
{

}

// ------------------------------------
void DumbKeyboardHandler::KeyDown(GLubyte key, int x, int y)
// ------------------------------------
{
	m_keys[key] = 1;
	if (m_keys[27])
		exit(0);
}

// ------------------------------------
void DumbKeyboardHandler::KeyUp(GLubyte key, int x, int y)
// ------------------------------------
{

}

// ------------------------------------
void KeyboardStack::KeyDown(GLubyte key, int x, int y)
// ------------------------------------
{
	std::vector<AbstractKeyboardHandler* >::iterator it;
	for (it = m_handlers.begin(); it != m_handlers.end(); it++)
	{
		(*it)->KeyDown(key, x, y);
	}
}

// ------------------------------------
void KeyboardStack::KeyUp(GLubyte key, int x, int y)
// ------------------------------------
{
	std::vector<AbstractKeyboardHandler* >::iterator it;
	for (it = m_handlers.begin(); it != m_handlers.end(); it++)
	{
		(*it)->KeyUp(key, x, y);
	}
}

// ------------------------------------
void KeyboardStack::PushKeyboardHandler(AbstractKeyboardHandler* handler)
// ------------------------------------
{
	if (handler)
		m_handlers.push_back(handler);
}

// ------------------------------------
void KeyboardStack::PopKeyboardHandler()
// ------------------------------------
{
	m_handlers.pop_back();
}
