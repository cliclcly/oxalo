// ****************************************************************************
// main.cpp
//
//
// ****************************************************************************

#include <stdio.h>

#include "engine/eEngineClass.h"

int main(int argc, char* argv[])
{
	int result = EngineClass::Initialize(600, 480);
	
	
	Square* s1 = new Square(10, 10);
	Triangle* s2 = new Triangle(8, 8);
	Square* s3 = new Square(12, 8);
	
	TerrainChunk* t1 = new TerrainChunk(7, 0);
	TerrainChunk* t2 = new TerrainChunk(5.5, 10); 
	Platform* p1 = new Platform( Vector2(0, 9), Vector2(2, 0.5));
	GenericEnemy* e1 = new GenericEnemy(7,12);
	//PSquare* s4 = new PSquare(10, 12);
	EngineClass::AddObject(s1);
	EngineClass::AddObject(s2);
	EngineClass::AddObject(s3);
	//EngineClass::AddObject(s4);
	EngineClass::AddObject(t1);
	EngineClass::AddObject(t2);
	EngineClass::AddObject(p1);
	
	EngineClass::AddStaticTextObject(new TextObject("This is a Block",9.25,10.75,GLUT_BITMAP_8_BY_13));
	EngineClass::AddRelativeTextObject(new TextObject("You are here, deal with it.",.4,.6,GLUT_BITMAP_8_BY_13));
	
	EngineClass::AddObject(e1);
	
	Player* p = new Player();
	EngineClass::AddObject(p);
	EngineClass::SetCamera(p);
	
	EngineClass::Run();

	return result;
}
