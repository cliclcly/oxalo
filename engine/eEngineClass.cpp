// ****************************************************************************
// eEngineClass.cpp
//
//
// ****************************************************************************

#include "eEngineClass.h"

#include <stdio.h>

#include "eAbstractObject.h"
#include "eMessage.h"

// ********************************************************
// EngineClass Statics
// ********************************************************

EngineClass* EngineClass::m_pInstance = NULL;

// ------------------------------------
EngineClass* EngineClass::Instance()
// ------------------------------------
{
	return m_pInstance;
}

// ------------------------------------
int EngineClass::Initialize(int width, int height)
// ------------------------------------
{
	if (m_pInstance) return 0;
	
	m_pInstance = new EngineClass();
	int result = m_pInstance->initialize(width, height);
	return result;
}

// ------------------------------------
void EngineClass::Run()
// ------------------------------------
{
	EngineClass* instance = Instance();
	instance->run();
}

// ------------------------------------
void EngineClass::GLDisplay()
// ------------------------------------
{
	EngineClass* instance = Instance();
	instance->glDisplay();
}

// ------------------------------------
void EngineClass::GLIdle()
// ------------------------------------
{
	EngineClass* instance = Instance();
	instance->glIdle();
}

// ------------------------------------
void EngineClass::GLReshape(int w, int h)
// ------------------------------------
{
	EngineClass* instance = Instance();
	instance->glReshape(w, h);
}

// ------------------------------------
void EngineClass::GLKeyDown(GLubyte key, int x, int y)
// ------------------------------------
{
	EngineClass* instance = Instance();
	instance->glKeyDown(key, x, y);
}

// ------------------------------------
void EngineClass::GLKeyUp(GLubyte key, int x, int y)
// ------------------------------------
{
	EngineClass* instance = Instance();
	instance->glKeyUp(key, x, y);
}

// ------------------------------------
int EngineClass::AddObject(AbstractObject* object)
// ------------------------------------
{
	EngineClass* instance = Instance();
	instance->addObject(object);
	return object->GUID;
}

// ------------------------------------
void EngineClass::RemoveObject(int GUID)
// ------------------------------------
{
	Instance()->removeObject(GUID);
}

// ------------------------------------
void EngineClass::SetCamera(Camera* cam)
// ------------------------------------
{
	Instance()->setCamera(cam);
}

// ********************************************************
// EngineClass
// ********************************************************

// ------------------------------------
EngineClass::EngineClass() :
// ------------------------------------
	m_lastGUID(0),
	m_zoom(1)
{

}

// ------------------------------------
EngineClass::~EngineClass()
// ------------------------------------
{

}

// ------------------------------------
int EngineClass::GetNextGUID()
// ------------------------------------
{
	m_lastGUID++;
	return m_lastGUID;
}

// ------------------------------------
int EngineClass::initialize(int width, int height)
// ------------------------------------
{
	char* argv[] = {(char* )"oxalo", (char* )""};
	int argc = 1;
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("oxalo");
	
	glutDisplayFunc(EngineClass::GLDisplay);
	glutIdleFunc(EngineClass::GLIdle);
	glutReshapeFunc(EngineClass::GLReshape);
	
	glutKeyboardFunc(EngineClass::GLKeyDown);
	glutKeyboardUpFunc(EngineClass::GLKeyUp);
	m_keyboardStack = new KeyboardStack();
	m_keyboardStack->PushKeyboardHandler(new DumbKeyboardHandler());
	
	m_objectHandler = new DumbObjectHandler();
	AbstractKeyboardHandler* kh = static_cast<AbstractKeyboardHandler* >(static_cast<DumbObjectHandler* >(m_objectHandler));
	m_keyboardStack->PushKeyboardHandler(kh);
	
	glDisable(GL_DEPTH_TEST);
	
	// Timing
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_currentTime);

	// initialize devIL
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	
	return 0;
}

// ------------------------------------
void EngineClass::run()
// ------------------------------------
{
	glutMainLoop();
}

// ------------------------------------
void EngineClass::glDisplay()
// ------------------------------------
{
	// Generate timing info
	LARGE_INTEGER newTime;
	QueryPerformanceCounter(&newTime);
	
	GLfloat diff = newTime.QuadPart - m_currentTime.QuadPart;
	diff /= m_frequency.QuadPart;
	
	m_currentTime = newTime;
	
	// Think
	ThinkMessage* tm = new ThinkMessage(diff);
	m_objectHandler->SendMessage(tm);
	delete tm;
	
	// Collisions
	m_objectHandler->FindCollisions(diff);
	
	// Graphics
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	
	// Do camera translation
	glTranslatef(-m_camera->GetX(), -m_camera->GetY(), 0);
	m_zoom = m_camera->GetZoom();
	glReshape(m_windowW, m_windowH);
	
	RenderMessage* rm = new RenderMessage();
	m_objectHandler->SendMessage(rm);
	delete rm;
	
	glFlush();
	
	glutSwapBuffers();
}

// ------------------------------------
void EngineClass::glIdle()
// ------------------------------------
{
	glutPostRedisplay();
}

// ------------------------------------
void EngineClass::glReshape(int w, int h)
// ------------------------------------
{
	float ar = (float) w / (float) h;
	if (h <= 0) h = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(-m_zoom * ar, m_zoom * ar, -m_zoom, m_zoom);
	glMatrixMode(GL_MODELVIEW);
	
	m_windowW = w;
	m_windowH = h;
}

// ------------------------------------
void EngineClass::glKeyDown(GLubyte key, int x, int y)
// ------------------------------------
{
	if (m_keyboardStack)
		m_keyboardStack->KeyDown(key, x, y);
}

// ------------------------------------
void EngineClass::glKeyUp(GLubyte key, int x, int y)
// ------------------------------------
{

}

// ------------------------------------
int EngineClass::addObject(AbstractObject* object)
// ------------------------------------
{
	m_objectHandler->AddObject(object);
	return object->GUID;
}

// ------------------------------------
void EngineClass::removeObject(int GUID)
// ------------------------------------
{
	m_objectHandler->RemoveObject(GUID);
}

// ------------------------------------
void EngineClass::setCamera(Camera* cam)
// ------------------------------------
{
	if (cam)
		m_camera = cam;
}

// ------------------------------------
void EngineClass::Shutdown()
// ------------------------------------
{

}
