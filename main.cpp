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
	PSquare* s4 = new PSquare(10, 12);
	EngineClass::AddObject(s1);
	EngineClass::AddObject(s2);
	EngineClass::AddObject(s3);
	EngineClass::AddObject(s4);
	Camerable* c = static_cast<Camerable* >(s1);
	EngineClass::SetCamera(c->GetCamera());
	
	EngineClass::Run();

	return result;
}
