// ****************************************************************************
// ePolygon.cpp
//
//
// ****************************************************************************

#include "ePolygon.h"

#include <iostream>
#include <math.h>

using namespace std;

// ------------------------------------
Vector2::Vector2() :
// ------------------------------------
	x(0),
	y(0)
{

}

// ------------------------------------
Vector2::Vector2(const Vector2& other) :
// ------------------------------------
	x(other.x),
	y(other.y)
{

}

// ------------------------------------
Vector2::Vector2(float x, float y) :
// ------------------------------------
	x(x),
	y(y)
{

}

// ------------------------------------
void Vector2::print()
// ------------------------------------
{
	cout << "[ " << x << ", " << y << "]" << endl;
}

// ------------------------------------
float Vector2::length()
// ------------------------------------
{
	return sqrt(x * x + y * y);
}

// ------------------------------------
Vector2 Vector2::normalize()
// ------------------------------------
{
	float l = length();
	return Vector2(x/l, y/l);
}

// ------------------------------------
Vector2 Vector2::operator+(const Vector2& other)
// ------------------------------------
{
	return Vector2(x + other.x, y + other.y);
}

// ------------------------------------
Vector2 Vector2::operator-(const Vector2& other)
// ------------------------------------
{
	return Vector2(x - other.x, y - other.y);
}

// ------------------------------------
float Vector2::operator*(const Vector2& other)
// ------------------------------------
{
	return x * other.x + y * other.y;
}

// ------------------------------------
int Vector2::operator==(const Vector2& other)
// ------------------------------------
{
	if (x == other.x && y == other.y)
		return true;
	return false;
}

// ------------------------------------
Box::Box()
// ------------------------------------
{
	base = Vector2(0, 0);
	dim = Vector2(1, 1);
}

// ------------------------------------
Box::Box(Vector2 b, Vector2 d)
// ------------------------------------
{
	base = b;
	dim = d;
}

// ------------------------------------
int Box::IsColliding(Box* other)
// ------------------------------------
{
	int cx = 0;
	int cy = 0;

	// check x collision
	if (base.x <= other->base.x && (base.x + dim.x) >= other->base.x)
		cx = 1;
	if (base.x <= (other->base.x + other->dim.x) &&
		(base.x + dim.x) >= (other->base.x + other->dim.x))
		cx = 1;
		
	// check y collision
	if (base.y <= other->base.y && (base.y + dim.y) >= other->base.y)
		cy = 1;
	if (base.y <= (other->base.y + other->dim.y) &&
		(base.y + dim.y) >= (other->base.y + other->dim.y))
		cy = 1;
		
	// colliding in both directions?
	if (cx && cy)
		return true;
	return false;
}

// ------------------------------------
Vector2 Box::NormalHitBy(const Vector2& pos, const Vector2& dir)
// ------------------------------------
{
	int left = 0; 
	int right = 0;
	int top = 0;
	int bot = 0;
	
	// Left side
	float time = (base.x - pos.x) / dir.x;
	float dy = time * dir.y + pos.y;
	if (dy >= base.y && dy <= (base.y + dim.y))
		left = 1;
		
	// right side
	time = (base.x + dim.x - pos.x) / dir.x;
	dy = time * dir.y + pos.y;
	if (dy >= base.y && dy <= (base.y + dim.y))
		right = 1;
		
	// bottom
	time = (base.y - pos.y) / dir.y;
	float dx = time * dir.x + pos.x;
	if (dx >= base.x && dx <= (base.x + dim.x))
		bot = 1;
		
	// top
	time = (base.y + dim.y - pos.y) / dir.y;
	dx = time * dir.x + pos.x;
	if (dx >= base.x && dx <= (base.x + dim.x))
		top = 1;
		
	if (pos.x < base.x) 
	{
		if (left)
			return Vector2(-1, 0);
		if (top)
			return Vector2(0, 1);
		if (bot)
			return Vector2(0, -1);
	}
	else if (pos.x < (base.x + dim.x))
	{
		if (pos.y < base.y)
		{
			if (bot)
				return Vector2(0, -1);
		}
		else if (pos.y > (base.y + dim.y))
		{
			if (top)
				return Vector2(0, 1);
		}
	}
	else if (pos.x > (base.x + dim.x))
	{
		if (right)
			return Vector2(1, 0);
		if (top)
			return Vector2(0, 1);
		if (bot)
			return Vector2(0, -1);
	}
		
	return Vector2(0, 0);
}

// ------------------------------------
Box* Box::Translate( float x, float y)
// ------------------------------------
{
	return new Box(Vector2(base.x + x, base.y + y), dim);
}
