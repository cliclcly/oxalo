// ****************************************************************************
// ePolygon.cpp
//
//
// ****************************************************************************

#include "ePolygon.h"

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "eDebug.h"

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
	cout << "[ " << x << ", " << y << "]";
}

// ------------------------------------
float Vector2::length() const
// ------------------------------------
{
	return sqrt(x * x + y * y);
}

// ------------------------------------
Vector2 Vector2::normalize() const
// ------------------------------------
{
	float l = length();
	return Vector2(x/l, y/l);
}

// ------------------------------------
float Vector2::dot(const Vector2& other) const
// ------------------------------------
{
	return x * other.x + y * other.y;
}

// ------------------------------------
Vector2 Vector2::scale(float s) const
// ------------------------------------
{
	return Vector2(x * s, y * s);
}

// ------------------------------------
Vector2 Vector2::project(const Vector2& other)
// ------------------------------------
{
	Vector2 ub = other.normalize();
	float d = dot(other);
	return ub.scale(d);
}

// ------------------------------------
Vector2 Vector2::operator+(const Vector2& other) const
// ------------------------------------
{
	return Vector2(x + other.x, y + other.y);
}

// ------------------------------------
Vector2 Vector2::operator+=(const Vector2& other)
// ------------------------------------
{
	x += other.x;
	y += other.y;
	return Vector2(x, y);
}

// ------------------------------------
Vector2 Vector2::operator-(const Vector2& other) const
// ------------------------------------
{
	return Vector2(x - other.x, y - other.y);
}

// ------------------------------------
Vector2 Vector2::operator-=(const Vector2& other)
// ------------------------------------
{
	return Vector2(x - other.x, y - other.y);
}

// ------------------------------------
Vector2 Vector2::operator-()
// ------------------------------------
{
	return Vector2(-x, -y);
}	

// ------------------------------------
float Vector2::operator*(const Vector2& other)
// ------------------------------------
{
	return dot(other);
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
Ray2::Ray2() : 
// ------------------------------------
	pos(Vector2(0, 0)),
	dir(Vector2(1, 0))
{
	
}

// ------------------------------------
Ray2::Ray2(const Ray2& other) :
// ------------------------------------
	pos(other.pos),
	dir(other.dir)
{

}

// ------------------------------------
Ray2::Ray2(const Vector2& p, const Vector2& d) :
// ------------------------------------
	pos(p),
	dir(d)
{

}

// ------------------------------------
int Ray2::Intersects(const Ray2& other) const
// ------------------------------------
{
	float det = dir.x * other.dir.y - dir.y * other.dir.x;
	if (det == 0)
		return false;
	return true;
}

// ------------------------------------
int Ray2::Intersects(const Segment2& other) const
// ------------------------------------
{
	Ray2 line = Ray2(other.p1, other.p2 - other.p1);
	if (!Intersects(line))
		return false;
	Vector2 point = IntersectionPoint(line);
	
	int x = (point.x >= other.p1.x) && (point.x <= other.p2.x) ||
			(point.x <= other.p1.x) && (point.x >= other.p2.x);
	int y = (point.y >= other.p1.y) && (point.y <= other.p2.y) ||
			(point.y <= other.p1.y) && (point.y >= other.p2.y);
			
	if (x && y)
		return true;
	return false;
}

// ------------------------------------
Vector2 Ray2::IntersectionPoint(const Ray2& other) const
// ------------------------------------
{
	float det = dir.x * other.dir.y - dir.y * other.dir.x;
	if (det == 0)
		return Vector2(0, 0);
	
	float num = dir.y * (other.pos.x - pos.x) - dir.x * (other.pos.y - pos.y);
	float tao = num / det;
	float t;
	if (dir.x != 0)
		t = (other.pos.x - pos.x + tao * other.dir.x) / dir.x;
	else
		t = (other.pos.y - pos.y + tao * other.dir.y) / dir.y;
		
	float ix = pos.x + t * dir.x;
	float iy = pos.y + t * dir.y;
	
	return Vector2(ix, iy);
}

// ------------------------------------
Vector2 Ray2::IntersectionPoint(const Segment2& other) const
// ------------------------------------
{
	if (Intersects(other))
		return IntersectionPoint(Ray2(other.p1, other.p2 - other.p1));
	return Vector2(0, 0);
}

// ------------------------------------
Segment2::Segment2() :
// ------------------------------------
	p1(Vector2(0, 0)),
	p2(Vector2(1, 0))
{

}

// ------------------------------------
Segment2::Segment2(const Segment2& other) :
// ------------------------------------
	p1(other.p1),
	p2(other.p2)
{
	
}

// ------------------------------------
Segment2::Segment2(const Vector2& a, const Vector2& b) :
// ------------------------------------
	p1(a),
	p2(b)
{

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
	Segment2 top = Segment2(base + Vector2(0, dim.y), base + dim);
	Segment2 bot = Segment2(base, base + Vector2(dim.x, 0));
	Segment2 left = Segment2(base, base + Vector2(0, dim.y));
	Segment2 right = Segment2(base + Vector2(dim.x, 0), base + dim);
	
	Ray2 r = Ray2(pos, dir);
	
	int ints = 0;
	int itop, ibot, ileft, iright;
	if (itop = r.Intersects(top)) ints++;
	if (ibot = r.Intersects(bot)) ints++;
	if (ileft = r.Intersects(left)) ints++;
	if (iright = r.Intersects(right)) ints++;
	
	if (ints == 1)
	{
		if (itop) return Vector2(0, 1);
		if (ibot) return Vector2(0, -1);
		if (ileft) return Vector2(-1, 0);
		if (iright) return Vector2(1, 0);
	}
	else
	{
		int sign = (pos.y - base.y) - (pos.x - base.x);
		int isign = (pos.y - base.y) + (pos.x - base.x);
		if (itop)
		{
			if (ileft)
			{
				if (isign >= 0) return Vector2(0, 1);
				else return Vector2(-1, 0);
			}
			if (iright)
			{
				if (sign >= 0) return Vector2(0, 1);
				else return Vector2(1, 0);
			}
			if (ibot)
			{
				if (pos.y >= base.y) return Vector2(0, 1);
				else return Vector2(0, -1);
			}
		}
		if (ibot)
		{
			if (ileft)
			{
				if (sign >= 0) return Vector2(-1, 0);
				else return Vector2(0, -1);
			}
			if (iright)
			{
				if (isign >= 0) return Vector2(1, 0);
				else return Vector2(0, -1);
			}
		}
		if (pos.x <= base.x) return Vector2(-1, 0);
		else return Vector2(1, 0);
	}
	
	return Vector2(0, 0);
}

// ------------------------------------
Box* Box::Translate( float x, float y)
// ------------------------------------
{
	return new Box(Vector2(base.x + x, base.y + y), dim);
}

// ------------------------------------
int Box::Contains(const Vector2& other)
// ------------------------------------
{
	int right = 0;
	int left = 0;
	int up = 0;
	int down = 0;
	
	if (other.x >= base.x) right = true;
	if (other.x <= (base.x + dim.x)) left = true;
	if (other.y >= base.y) down = true;
	if (other.y <= (base.y + dim.y)) up = true;
	
	if (right && left && up && down)
		return true;
	return false;
}

// ------------------------------------
Vector2 Box::IntersectionPoint(const Ray2& other)
// ------------------------------------
{
	Segment2 top = Segment2(base + Vector2(0, dim.y), base + dim);
	Segment2 bot = Segment2(base, base + Vector2(dim.x, 0));
	Segment2 left = Segment2(base, base + Vector2(0, dim.y));
	Segment2 right = Segment2(base + Vector2(dim.x, 0), base + dim);
	
	int ints = 0;
	int itop, ibot, ileft, iright;
	if (itop = other.Intersects(top)) ints++;
	if (ibot = other.Intersects(bot)) ints++;
	if (ileft = other.Intersects(left)) ints++;
	if (iright = other.Intersects(right)) ints++;
	
	printf("Segs: ");
	if (itop) printf("top ");
	if (ibot) printf("bot ");
	if (ileft) printf("left ");
	if (iright) printf("right ");
	printf("\n");
	
	if (ints == 1)
	{
		if (itop) return other.IntersectionPoint(top);
		if (ibot) return other.IntersectionPoint(bot);
		if (ileft) return other.IntersectionPoint(left);
		if (iright) return other.IntersectionPoint(right);
	}
	else
	{
		int sign = (other.pos.y - base.y) - (other.pos.x - base.x);
		int isign = (other.pos.y - base.y) + (other.pos.x - base.x);
		if (itop)
		{
			if (ileft)
			{
				if (other.pos.x <= base.x) return other.IntersectionPoint(left);
				if (other.pos.x <= (base.x + dim.x))
				{
					if (other.dir.x + other.dir.y > 0) return other.IntersectionPoint(top);
					else return other.IntersectionPoint(left);
				}
				return other.IntersectionPoint(top);
			}
			if (iright)
			{
				if (other.pos.x <= base.x) return other.IntersectionPoint(top);
				if (other.pos.x <= (base.x + dim.x))
				{
					if (other.dir.y - other.dir.x > 0) return other.IntersectionPoint(top);
					else return other.IntersectionPoint(right);
				}
				return other.IntersectionPoint(right);
			}
			if (ibot)
			{
				if (other.pos.y > base.y) 
				{
					if (other.pos.y < (base.y + dim.y))
					{
						if (other.dir.y >= 0)
							return other.IntersectionPoint(top);
						else
							return other.IntersectionPoint(bot);
					}
					return other.IntersectionPoint(top);
				}
				else return other.IntersectionPoint(bot);
			}
		}
		if (ibot)
		{
			if (ileft)
			{
				if (other.pos.x <= base.x) return other.IntersectionPoint(left);
				if (other.pos.x <= (base.x + dim.x))
				{
					if (other.pos.y > base.y)
					{
						if (other.dir.y - other.dir.x > 0) return other.IntersectionPoint(left);
						else return other.IntersectionPoint(bot);
					}
					return other.IntersectionPoint(bot);
				}
				return other.IntersectionPoint(bot);
			}
			if (iright)
			{
				if (isign >= 0) return other.IntersectionPoint(right);
				else return other.IntersectionPoint(bot);
			}
		}
		if (other.pos.x <= base.x) return other.IntersectionPoint(left);
		else 
		{
			if (other.pos.x <= (base.x + dim.x))
			{
				if (other.dir.x < 0)
					return other.IntersectionPoint(left);
				else
					return other.IntersectionPoint(right);
			}
			return other.IntersectionPoint(right);
		}
	}
	
	return Vector2(0, 0);
}
