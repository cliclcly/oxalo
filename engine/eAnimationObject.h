// ****************************************************************************
// eAnimationObject.h
//
//
// ****************************************************************************

#ifndef _ANIMATIONOBJECT_H_
#define _ANIMATIONOBJECT_H_

#include "enums.h"

#include <GL/gl.h>
#include <map>
#include <string>

class AnimationObject
{
public:
	AnimationObject(ANIM,std::string,int,int);
	GLuint getGUID();
	
	std::string m_path;
	int m_frameNum;
	int m_frameRate;
	
	ANIM m_anim;
private:
	GLuint m_animID;	

};

class AnimationSet
{
public: 
	AnimationSet(std::string,COLOR);
	void BuildAnimationObject(ANIM,std::string,int,int);
	AnimationObject * GetAnimationObject(ANIM);
	
	std::map<ANIM,AnimationObject*> m_set;
	
	std::string m_type;
	COLOR m_color;
	
	
};


#endif