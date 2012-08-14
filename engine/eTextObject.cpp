// ****************************************************************************
// eTextObject.cpp
//
//
// ****************************************************************************

#include "eTextObject.h"
#include <windows.h>
#include <GL/glut.h>

// ------------------------------------
TextObject::TextObject(std::string text, void* font) :
// ------------------------------------
	m_text(text),
	m_xPos(0),
	m_yPos(0),
	m_font(font)
{

}

// ------------------------------------
TextObject::TextObject(std::string text,float xPos,float yPos, void* font):
// ------------------------------------
	m_text(text),
	m_xPos(xPos),
	m_yPos(yPos),
	m_font(font)
{

}
 // ------------------------------------
 void TextObject::render()
 // ------------------------------------
 {
	glPushMatrix();	
	glRasterPos2f(m_xPos,m_yPos);
	for(int i=0;i<m_text.size();i++)
	{
		glutBitmapCharacter(m_font,m_text[i]);
	}
	glPopMatrix();
 }