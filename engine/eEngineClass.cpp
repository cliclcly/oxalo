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

//EngineClass::derp = 10;

 std::string EngineClass::colorString[] = {"red",
									"green",
									"blue",
									"orange",
									"purple",
									"yellow",
									"white",
									"black"};

 std::string EngineClass::animString[] = {"still",
									"walking",
									"prejump",
									"jump",
									"landing",
									"attack",
									"die"};
									

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
void EngineClass::CreateAnimationDictionary()
// ------------------------------------
{
	printf("derp\n");
	for(int i=0;i<enemyTypes->m_children.size();i++)
	{
		std::string path = "Textures/";
		XMLNode * temp = enemyTypes->m_children.at(i)->findChild("EnemyName");
		if(temp==NULL) { throw new std::exception(); }
		std::string enemyType = temp->m_value;
		printf("enemyType: |%s|\n",enemyType.c_str());
		path+=enemyType;
		path+="/animation.config";
		printf("path: %s\n",path.c_str());
		XMLNode * conf = XMLParser::Parse(path);
		printf("derp\n");
		for(int c = COLOR_FIRST;c<COLOR_LAST;c++)
		{
			AnimationSet* temp = new AnimationSet(enemyType);
			m_animationDictionary.insert(std::pair<  std::pair<std::string,COLOR>,AnimationSet*>
					(std::pair<std::string,COLOR>(enemyType,(COLOR)c),temp));
			std::string base = "Textures/";
			base+=enemyType;
			base += "/";
			base += EngineClass::colorString[c];
			base += "/";
			for (int i=ANIM_FIRST;i<=ANIM_LAST;i++)
			{
				XMLNode * anim = conf->findChild(EngineClass::animString[i]);
				if(anim==NULL){throw new std::exception();}
				XMLNode * frameNum = anim->findChild("frameNum");
				XMLNode * frameRate = anim->findChild("frameRate");
				if(frameNum==NULL || frameRate==NULL){throw new std::exception();}
				printf("loop: %d\n",i);
				std::string path = base;
				path+=EngineClass::animString[i];
				path+=".png";
				temp->BuildAnimationObject((ANIM)i,path,atoi(frameNum->m_value.c_str()),atoi(frameRate->m_value.c_str()));
			}
			
		}
	}

	//will read config file eventually
	//for now, will be hard coded
	/*m_animationDictionary.insert(std::pair<  std::pair<std::string,COLOR>,AnimationSet*>
					(std::pair<std::string,COLOR>(std::string("slime"),COLOR_BLUE),new AnimationSet(std::string("slime"))));
					
	AnimationSet* temp = m_animationDictionary.find(std::pair<std::string,COLOR>(std::string("slime"),COLOR_BLUE))->second;
	std::string base = "Textures/slime/";
	base += EngineClass::colorString[COLOR_BLUE];
	base += "/";
	for (int i=ANIM_FIRST;i<=ANIM_LAST;i++)
	{
		printf("loop: %d\n",i);
		std::string path = base;
		path+=EngineClass::animString[i];
		path+=".png";
		temp->BuildAnimationObject((ANIM)i,path,5,30);
	}
	*/
	std::map<std::pair<std::string,COLOR>, AnimationSet*>::iterator p = m_animationDictionary.begin();
	for(p=m_animationDictionary.begin();p!=m_animationDictionary.end();p++)
	{
		printf("\n dictionary: %d %d\n",p->first.first.c_str(),p->first.second);
		std::map<ANIM,AnimationObject*> tempSet = p->second->m_set;
		std::map<ANIM,AnimationObject*>::iterator q = tempSet.begin();
		for(q=tempSet.begin();q!=tempSet.end();q++)
		{
			printf("entry: %d\n",q->first);
			AnimationObject* tempAO = q->second;
			printf("values: %s %d %d\n", tempAO->m_path.c_str(),tempAO->m_frameNum, tempAO->m_frameRate);
		}
	}
}

// ------------------------------------
void EngineClass::Run()
// ------------------------------------
{
	EngineClass* instance = Instance();
	instance->run();
}

// ------------------------------------
AnimationSet * EngineClass::GetAnimationSet(std::string objType,COLOR color)
// ------------------------------------
{
	EngineClass* instance = Instance();
	std::map<std::pair<std::string,COLOR>, AnimationSet*>::iterator p = instance->m_animationDictionary.begin();
	for(p=instance->m_animationDictionary.begin();p!=instance->m_animationDictionary.end();p++)
	{
		printf("\n dictionary: %d %d\n",p->first.first.c_str(),p->first.second);
		std::map<ANIM,AnimationObject*> tempSet = p->second->m_set;
		std::map<ANIM,AnimationObject*>::iterator q = tempSet.begin();
		for(q=tempSet.begin();q!=tempSet.end();q++)
		{
			printf("entry: %d\n",q->first);
			AnimationObject* tempAO = q->second;
			printf("values: %s %d %d\n", tempAO->m_path.c_str(),tempAO->m_frameNum, tempAO->m_frameRate);
		}
	}
	
	return instance->m_animationDictionary.find(std::pair<std::string,COLOR>(objType,color))->second;
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
void EngineClass::SetCamera(AbstractObject* o)
// ------------------------------------
{
	Instance()->setCamera(o);
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
	glutIgnoreKeyRepeat(true);
	m_keyboardStack = new KeyboardStack();
	m_keyboardStack->PushKeyboardHandler(new DumbKeyboardHandler());
	
	m_objectHandler = new DumbObjectHandler();
	AbstractKeyboardHandler* kh = static_cast<AbstractKeyboardHandler* >(static_cast<DumbObjectHandler* >(m_objectHandler));
	m_keyboardStack->PushKeyboardHandler(kh);
	
	m_camera = new Camera(new float(0.0), new float(0.0), new float(4.0));
	
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	
	// Timing
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_currentTime);
	printf("Freq: %u\n", m_frequency.QuadPart);
	printf("Current: %u\n", m_currentTime.QuadPart);
	m_tockTime=0;
	
	// initialize devIL
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	
	//load enemy configs
	loadEnemies();
	// initialize animation dictionary
	CreateAnimationDictionary();
	
	
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
	m_tockTime += diff;
	if (m_tockTime > 1)
	{
		m_tockTime -= 1;
		m_tock = 1;
	}
	
	m_currentTime = newTime;
	
	
	float interval = 1.0/100.0;
	m_cumTime += diff;
	if (m_cumTime > interval)
	{
		if (USE_SPECULATIVE_CONTACTS)
		{
			
		}
		
		// Think
		ThinkMessage* tm = new ThinkMessage(interval, m_tock);
		m_objectHandler->SendMessage(tm);
		delete tm;
		
		// Collisions
		if (!USE_SPECULATIVE_CONTACTS)
		{
			int iterations = 1; int i;
			for (i = 0; i < iterations; i++)
			{
				m_objectHandler->FindCollisions(diff);
			}
			m_cumTime -= interval;
		}
	}
	
	// Graphics
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	
	// Do camera translation
	glTranslatef(-m_camera->GetX(), -m_camera->GetY(), 0);
	m_zoom = m_camera->GetZoom();
	glReshape(m_windowW, m_windowH);
	
	// render
	RenderMessage* rm = new RenderMessage(EMSG_RENDER);
	m_objectHandler->SendMessage(rm);
	delete rm;
	
	// render HUD
	glHUD(m_windowW, m_windowH);
	rm = new RenderMessage(EMSG_RENDER_HUD);
	m_objectHandler->SendMessage(rm);
	delete rm;
	
	m_tock = false;
	
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
void EngineClass::glHUD(int w, int h)
// ------------------------------------
{
	float ar = (float) w / (float) h;
	if (h <= 0) h = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, 1 * ar, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
	if (m_keyboardStack)
		m_keyboardStack->KeyUp(key, x, y);
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
void EngineClass::setCamera(AbstractObject* o)
// ------------------------------------
{
	if (o)
	{
		if (o->RespondsTo(EMSG_SPATIAL))
		{
			SpatialAttr* sa = 
				static_cast<SpatialAttr* >(o->GetAttribute(EATTR_SPATIAL));
			printf("X: %f Y: %f\n", sa->pos.x, sa->pos.y);
			if (m_camera)
				delete m_camera;
			m_camera = new Camera(&(sa->pos.x), &(sa->pos.y), new float(4.0));
		}
	}
}
// ------------------------------------
void EngineClass::loadEnemies()
// ------------------------------------
{
	enemyTypes = new XMLNode("EnemyDictionary");

	//printf("loading\n");
	WIN32_FIND_DATA tempStore;
	//printf("loading\n");
	HANDLE search = FindFirstFile("Enemies/*.config",&tempStore);
	//printf("loading\n");
	if (search == INVALID_HANDLE_VALUE)
	{
		printf("Invalid file handle.\n");
	}
	else
	{
		std::string base = "Enemies/";
		base+=tempStore.cFileName;
		XMLNode * temp = XMLParser::Parse(base);
		if(verifyEnemy(temp))
		{
			XMLNode * toAdd = new XMLNode("Enemy");
			toAdd->m_children.push_back(temp);
			enemyTypes->m_children.push_back(toAdd);
		}
		printf ("First file name is %s.\n", base.c_str());
		while (FindNextFile(search,&tempStore)!=false)
		{
			std::string base = "Enemies/";
			base+=tempStore.cFileName;
			temp = XMLParser::Parse(base);
			if(verifyEnemy(temp))
			{
				enemyTypes->m_children.push_back(temp);
			}
			printf ("Next file name is %s.\n",base.c_str());
		}
	}
	
}

// ------------------------------------
bool EngineClass::verifyEnemy(XMLNode* toVerify)
// ------------------------------------
{
	return true;
}

// ------------------------------------
void EngineClass::Shutdown()
// ------------------------------------
{

}
