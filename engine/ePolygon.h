// ****************************************************************************
// ePolygon.h
//
//
// ****************************************************************************

#ifndef __EPOLYGON_H__
#define __EPOLYGON_H__

class Vector2
{
public:
	float x, y;
	
	Vector2();
	Vector2(const Vector2& other);
	Vector2(float x, float y);
	
	void print();
	
	float length();
	Vector2 normalize();
	
	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	float operator*(const Vector2& other);
	int operator==(const Vector2& other);
};

class Box
{
public:
	Vector2 base;
	Vector2 dim;

	Box();
	Box( Vector2 , Vector2);
	
	int IsColliding(const Box& other);
	Vector2 NormalHitBy(const Vector2& pos, const Vector2& dir);
};

#endif
