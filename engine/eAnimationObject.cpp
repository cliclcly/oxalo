// ****************************************************************************
// eAnimationObject.cpp
//
//
// ****************************************************************************

#include "eAnimationObject.h"
#include "eAttribute.h"
#include "eEngineClass.h"


// ------------------------------------
AnimationObject::AnimationObject(ANIM anim,std::string path,int numFrames,int framerate):
// ------------------------------------
	m_anim(anim),
	m_path(path),
	m_frameNum(numFrames),
	m_frameRate(framerate),
	m_animID(0)
{
	printf("%s\n",path.c_str());
}

// ------------------------------------
GLuint AnimationObject::getGUID()
// ------------------------------------
{
	if (m_animID==0)
	{
		printf("loading texture: %s\n",m_path.c_str());
		m_animID = ilutGLLoadImage((char*)m_path.c_str());
		printf("loading texture finished: %d\n",m_animID);
	}
	printf("returning %d\n",m_animID);
	return m_animID;
}

// ------------------------------------
AnimationSet::AnimationSet(std::string objType):
// ------------------------------------
	m_type(objType)
{

}

// ------------------------------------
void AnimationSet::BuildAnimationObject(ANIM anim,std::string path,int numFrames,int framerate)
// ------------------------------------
{
	//std::pair<std::map<ANIM,AnimationObject*>::iterator, bool> temp = 
	m_set.insert(std::pair<ANIM,AnimationObject*>(anim, new AnimationObject(anim,path,numFrames,framerate)));
}

// ------------------------------------
AnimationObject * AnimationSet::GetAnimationObject(ANIM anim)
// ------------------------------------
{
	m_set.find(anim);
	printf("got here, almost\n");
	if(m_set.find(anim)==m_set.end())
	{
		printf("derpy derpy derp\n");
	}
	AnimationObject * temp = m_set.find(anim)->second;
	if (temp==NULL)
	{
		printf("temp null\n");
	}
	else
	{
		printf("temp not null\n");
	}
	return temp;
}
