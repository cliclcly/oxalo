// ****************************************************************************
// ePolygon.h
//
//
// ****************************************************************************

#ifndef __EPOLYGON_H__
#define __EPOLYGON_H__

#include <vector>
#include <set>

class Vector2;
class Ray2;
class Segment2;
class Box;
class Mesh;

// ------------------------------------
class Vector2
// ------------------------------------
{
public:
	float x, y;
	
	Vector2();
	Vector2(const Vector2& other);
	Vector2(float x, float y);
	
	void print() const;
	
	float length() const;
	Vector2 normalize() const;
	float dot(const Vector2& other) const;
	Vector2 scale(float ) const;
	Vector2 project(const Vector2& other);
	Vector2 ClockwiseNormal() const;
	Vector2 TripleProduct(const Vector2& other);
	
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator-=(const Vector2& other);
	Vector2 operator-();
	float operator*(const Vector2& other);
	int operator==(const Vector2& other) const;
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
	float distToOrigin;
	
	Segment2();
	Segment2(const Segment2& other);
	Segment2(const Vector2& a, const Vector2& b);
	
	void Print();
	Vector2 Normal();
	
	int IsClockwise(const Vector2& p);
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
	
	int IsColliding(Box other);
	Vector2 NormalHitBy(const Vector2& pos, const Vector2& dir);
	Box Translate( float, float);
	int Contains(const Vector2& pos);
	Vector2 IntersectionPoint(const Ray2& other);
};

// ------------------------------------
class Mesh
// ------------------------------------
{
// Assumes points added are in clockwise order
// Assumes convex
public:
	Mesh();
	Mesh(std::vector<Vector2 > points);
	Mesh(Box b);

	std::vector<Vector2 > points;
	
	void AddPoint(const Vector2& point);
	int Size();
	void Print();
	void Translate(const Vector2& other);
	Mesh MeshTranslatedBy(const Vector2& other);
	
	Box GetAABB();
	Vector2 GetFarthestPointInDirection(const Vector2& dir);
	Vector2 Support(Mesh b, const Vector2& dir);
	int Contains(const Vector2& p);
	int HasVertex(const Vector2& p);
	
	
	// GJK ----------------------------
	void GJKEnsureClockwise();
	void GJKAddPoint(const Vector2& other);
	Vector2 GJKGetNextDirection();
	
	int GJK(Mesh b);
	int GJK(Mesh b, const Vector2& dir);
	
	// EPA ----------------------------
	void EPAAddPoint(Vector2 p, Vector2 toAdd);
	Segment2 EPAGetClosestEdge();
	
	std::pair<float, Vector2> EPA(Mesh b);
	
	void DistAddPoint(const Vector2& other);
	float Distance(Mesh other);
};

#endif
