// ****************************************************************************
// main.cpp
//
//
// ****************************************************************************

#include <stdio.h>

#include "engine/eEngineClass.h"
#include <vector>

int main(int argc, char* argv[])
{
	std::vector<Vector2 > points;
	points.push_back(Vector2(0, 0));
	points.push_back(Vector2(0, 1));
	points.push_back(Vector2(2, 1));
	points.push_back(Vector2(2, 0));
	Mesh m1 = Mesh(points);
	
	std::vector<Vector2 > points2;
	points2.push_back(Vector2(0.5, 0.5));
	points2.push_back(Vector2(0.5, 1.5));
	points2.push_back(Vector2(1.5, 1.5));
	points2.push_back(Vector2(1.5, 0.5));
	Mesh m2 = Mesh(points2);
	
	std::vector<Vector2 > points3;
	points3.push_back( Vector2(-0.5, 0.6));
	points3.push_back( Vector2(-0.5, 1.0));
	points3.push_back( Vector2(1.0, -0.5));
	points3.push_back( Vector2(0.6, -0.5));
	Mesh m3 = Mesh(points3);
	
	
	int result = EngineClass::Initialize(600, 480);
	
	Square* s1 = new Square(10, 10);
	Triangle* s2 = new Triangle(8, 8);
	Square* s3 = new Square(12, 8);
	
	TerrainChunk* t1 = new TerrainChunk(7, 0);
	TerrainChunk* t2 = new TerrainChunk(5.5, 10); 
	Platform* p1 = new Platform( Vector2(0, 9), Vector2(2, 0.5));
	//GenericEnemy* e1 = new GenericEnemy(7,12);
	//PSquare* s4 = new PSquare(10, 12);
	EngineClass::AddObject(s1);
	EngineClass::AddObject(s2);
	EngineClass::AddObject(s3);
	//EngineClass::AddObject(s4);
	EngineClass::AddObject(t1);
	EngineClass::AddObject(t2);
	EngineClass::AddObject(p1);
	
	//EngineClass::AddObject(e1);
	
	Player* p = new Player();
	EngineClass::AddObject(p);
	EngineClass::SetCamera(p);
	
	EngineClass::Run();

	return result;
	
	
	return 0;
}
