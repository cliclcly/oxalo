// ****************************************************************************
// eEngineClass.h
// 
//
// ****************************************************************************

#ifndef _ENGINECLASS_H_
#define _ENGINECLASS_H_

#include <windows.h>
#include <map>
#include <string>

#include <GL/glut.h>
#include <IL/ilut.h>

#include "ePolygon.h"
#include "eAbstractObject.h"
#include "eTextObject.h"
#include "eObjectHandler.h"
#include "eAbstractKeyboardHandler.h"
#include "eCamera.h"
#include "eDebug.h"
#include "ePlayer.h"
#include "eTerrainChunk.h"
#include "ePlatform.h"
#include "genericEnemy.h"
#include "eAnimationObject.h"
#include "eXMLParser.h"
#include "iLoggable.h"
#include "eLogger.h"

#define USE_SPECULATIVE_CONTACTS 0


class EngineClass
{
public: // Methods
	static EngineClass* Instance();
	static int Initialize(int, int);
	static void Run();
	static AnimationSet * GetAnimationSet(std::string,COLOR);
	
	// Static OpenGL Callbacks
	static void GLDisplay();
	static void GLIdle();
	static void GLReshape(int, int);
	static void GLKeyDown(GLubyte key, int x, int y);
	static void GLKeyUp(GLubyte key, int x, int y);
	
	// Objects
	int GetNextGUID();
	static int AddObject(AbstractObject* );
	static int AddStaticTextObject(TextObject* );
	static int AddRelativeTextObject(TextObject* );
	static void RemoveObject(int GUID);
	
	
	static  std::string colorString[];
	static  std::string animString[];
	
	
	// Camera
	static void SetCamera(AbstractObject* );
		
	
	void Shutdown();
	
public: // Members
	std::map<std::pair<std::string,COLOR>, AnimationSet*> m_animationDictionary;
	
private: // Methods
	EngineClass();
	~EngineClass();
	
	int initialize(int , int );
	void CreateAnimationDictionary();
	void run();
	
	// Private OpenGL Callbacks
	void glDisplay();
	void glIdle();
	void glReshape(int, int);
	void glHUD(int, int);
	void glKeyDown(GLubyte key, int x, int y);
	void glKeyUp(GLubyte key, int x, int y);
	
	// Objects
	int addObject(AbstractObject* );
	int addStaticTextObject(TextObject* );
	int addRelativeTextObject(TextObject* );
	void removeObject(int GUID);
	
	// Camera
	void setCamera(AbstractObject* );
	
	//enemies
	void loadEnemies();
	bool verifyEnemy(XMLNode*);
	
	
private: // Members
	static EngineClass* m_pInstance;
	
	ObjectHandler* m_objectHandler;
	RelativeTextObjectHandler* m_relativeTextObjectHandler;
	StaticTextObjectHandler* m_staticTextObjectHandler;
	KeyboardStack* m_keyboardStack;
	
	Camera* m_camera;
	float m_zoom;
	int m_windowW;
	int m_windowH;
	
	LARGE_INTEGER m_frequency;
	LARGE_INTEGER m_currentTime;
	
	//enemies
	XMLNode * enemyTypes;
	
	// tock
	float m_tockTime;
	int m_tock;
	
	// physics time step
	float m_cumTime;
	
	int m_lastGUID;
};


#endif
