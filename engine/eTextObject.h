// ****************************************************************************
// eTextObject.h
//
//
// ****************************************************************************

#ifndef __ETEXTOBJECT_H__
#define __ETEXTOBJECT_H__

#include <string>

// ------------------------------------
class TextObject
// ------------------------------------
{
public:
	TextObject(std::string,void*);
	TextObject(std::string,float,float,void*);
	void render();
	
	std::string m_text;
	
	void* m_font;
	float m_xPos;
	float m_yPos;
};

#endif