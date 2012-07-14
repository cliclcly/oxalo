// ****************************************************************************
// eEngineClass.h
// 
//
// ****************************************************************************

#ifndef _ENGINECLASS_H_
#define _ENGINECLASS_H_

#include <windows.h>

#include <GL/glut.h>
#include <IL/ilut.h>

#include "ePolygon.h"
#include "eAbstractObject.h"
#include "eObjectHandler.h"
#include "eAbstractKeyboardHandler.h"
#include "eCamera.h"
#include "eDebug.h"
#include "ePlayer.h"
#include "eTerrainChunk.h"
#include "ePlatform.h"
#include "genericEnemy.h"

#define USE_SPECULATIVE_CONTACTS 0

class EngineClass
{
public: // Methods
	static EngineClass* Instance();
	static int Initialize(int, int);
	static void Run();
	
	// Static OpenGL Callbacks
	static void GLDisplay();
	static void GLIdle();
	static void GLReshape(int, int);
	static void GLKeyDown(GLubyte key, int x, int y);
	static void GLKeyUp(GLubyte key, int x, int y);
	
	// Objects
	int GetNextGUID();
	static int AddObject(AbstractObject* );
	static void RemoveObject(int GUID);
	
	// Camera
	static void SetCamera(AbstractObject* );
	
	void Shutdown();
	
public: // Members

private: // Methods
	EngineClass();
	~EngineClass();
	
	int initialize(int , int );
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
	void removeObject(int GUID);
	
	// Camera
	void setCamera(AbstractObject* );
	
private: // Members
	static EngineClass* m_pInstance;
	
	ObjectHandler* m_objectHandler;
	KeyboardStack* m_keyboardStack;
	
	Camera* m_camera;
	float m_zoom;
	int m_windowW;
	int m_windowH;
	
	LARGE_INTEGER m_frequency;
	LARGE_INTEGER m_currentTime;
	
	// tock
	float m_tockTime;
	int m_tock;
	
	// physics time step
	float m_cumTime;
	
	int m_lastGUID;
};

#endif
