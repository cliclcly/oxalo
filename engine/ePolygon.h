// ****************************************************************************
// ePolygon.h
//
//
// ****************************************************************************

#ifndef __EPOLYGON_H__
#define __EPOLYGON_H__

#include <vector>

class Vector2;
class Ray2;
class Segment2;
class Box;
class Polygon;

// ------------------------------------
class Vector2
// ------------------------------------
{
public:
	float x, y;
	
	Vector2();
	Vector2(const Vector2& other);
	Vector2(float x, float y);
	
	void print();
	
	float length() const;
	Vector2 normalize() const;
	float dot(const Vector2& other) const;
	Vector2 scale(float ) const;
	Vector2 project(const Vector2& other);
	
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator-=(const Vector2& other);
	Vector2 operator-();
	float operator*(const Vector2& other);
	int operator==(const Vector2& other);
};

// ------------------------------------
class Ray2
// ------------------------------------
{
public:
	Vector2 pos;
	Vector2 dir;
	
	Ray2();
	Ray2(const Ray2& other);
	Ray2(const Vector2& p, const Vector2& d);
	
	int Intersects(const Ray2& other) const ;
	int Intersects(const Segment2& other) const;
	Vector2 IntersectionPoint(const Ray2& other) const;
	float IntersectionTime(const Ray2& other) const;
	Vector2 IntersectionPoint(const Segment2& other) const;
	
};

// ------------------------------------
class Segment2
// ------------------------------------
{
public:
	Vector2 p1;
	Vector2 p2;
	
	Segment2();
	Segment2(const Segment2& other);
	Segment2(const Vector2& a, const Vector2& b);
};

// ------------------------------------
class Box
// ------------------------------------
{
public:
	Vector2 base;
	Vector2 dim;

	Box();
	Box( Vector2 , Vector2);
	
	void Print();
	
	int IsColliding(Box* other);
	Vector2 NormalHitBy(const Vector2& pos, const Vector2& dir);
	Box* Translate( float, float);
	int Contains(const Vector2& pos);
	Vector2 IntersectionPoint(const Ray2& other);
};

// ------------------------------------
class Mesh
// ------------------------------------
{
public:
	Mesh();
	Mesh(std::vector<Vector2 > points);

	std::vector<Vector2 > points;
	
	void AddPoint(const Vector2& point);
	int Size();
	void Print();
	void Translate(const Vector2& other);
	
	Box GetAABB();
	Vector2 Support(const Vector2& dir);
};

#endif
