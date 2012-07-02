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
	//PSquare* s4 = new PSquare(10, 12);
	EngineClass::AddObject(s1);
	EngineClass::AddObject(s2);
	EngineClass::AddObject(s3);
	//EngineClass::AddObject(s4);
	EngineClass::AddObject(t1);
	EngineClass::AddObject(t2);
	
	Player* p = new Player();
	EngineClass::AddObject(p);
	EngineClass::SetCamera(p);
	
	EngineClass::Run();

	return result;
}
