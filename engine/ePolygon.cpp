// ****************************************************************************
// ePolygon.cpp
//
//
// ****************************************************************************

#include "ePolygon.h"

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <float.h>
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
void Vector2::print() const
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
	if (l == 0) return Vector2(x, y);
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
Vector2 Vector2::ClockwiseNormal() const
// ------------------------------------
{
	return Vector2(y, -x);
}

// ------------------------------------
Vector2 Vector2::TripleProduct(const Vector2& other)
// ------------------------------------
{
	float z = x * other.y - y * other.x;
	return Vector2(-z * other.y, z * other.x);
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
int Vector2::operator==(const Vector2& other) const
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
	{
		return false;
	}
			
	float time = IntersectionTime(line);
	if (time >= 0 && time <= 1)
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
float Ray2::IntersectionTime(const Ray2& other) const
// ------------------------------------
{
	float det = dir.x * other.dir.y - dir.y * other.dir.x;
	if (det == 0)
		return FLT_MAX;
	
	float num = dir.y * (other.pos.x - pos.x) - dir.x * (other.pos.y - pos.y);
	float tao = num / det;
	float t;
	if (dir.x != 0)
		t = (other.pos.x - pos.x + tao * other.dir.x) / dir.x;
	else
		t = (other.pos.y - pos.y + tao * other.dir.y) / dir.y;
		
	return tao;
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
void Segment2::Print()
// ------------------------------------
{
	p1.print();
	printf(" to ");
	p2.print();
	printf("\n");
}

// ------------------------------------
Vector2 Segment2::Normal()
// ------------------------------------
{
	Vector2 d = p2 - p1;
	Vector2 p1o = -p1;
	return p1o.TripleProduct(d).normalize();
}

// ------------------------------------
int Segment2::IsClockwise(const Vector2& p)
// ------------------------------------
{
	Vector2 s = p2 - p1;
	Vector2 n = s.ClockwiseNormal();
	Vector2 d = p - p1;
	if (d.dot(n) >= 0) return true;
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
void Box::Print()
// ------------------------------------
{
	printf("Box: ");
	base.print();
	printf(" ");
	dim.print();
	printf("\n");
}

// ------------------------------------
int Box::IsColliding(Box other)
// ------------------------------------
{
	int cx = 0;
	int cy = 0;
	
	// check x collision
	if ((base.x >= other.base.x) && (base.x <= (other.base.x + other.dim.x)))
		cx = 1;
	if (((base.x + dim.x) >= other.base.x) && ((base.x + dim.x) <= (other.base.x + other.dim.x)))
		cx = 1;
		
	if ((other.base.x >= base.x) && (other.base.x <= (base.x + dim.x)))
		cx = 1;
	if (((other.base.x + other.dim.x) >= base.x) && ((other.base.x + other.dim.x) <= (base.x + dim.x)))
		cx = 1;	
		
	if ( (base.y >= other.base.y) && (base.y <= (other.base.y + other.dim.y) ) )
	{
		cy = 1;
	}
	if ( ( (base.y + dim.y) >= other.base.y) && ( (base.y + dim.y) <= (other.base.y + other.dim.y)))
	{
		cy = 1;
	}
	
	if ( (other.base.y >= base.y) && (other.base.y <= (base.y + dim.y) ) )
	{
		cy = 1;
	}
	if ( ( (other.base.y + other.dim.y) >= base.y) && ( (other.base.y + other.dim.y) <= (base.y + dim.y)))
	{
		cy = 1;
	}
		
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
		if (itop)
		{
			if (ileft)
			{
				if (pos.x <= base.x) return Vector2(-1, 0);
				if (pos.x <= (base.x + dim.x))
				{
					if (pos.y <= (base.y + dim.y))
					{
						if (dir.x >= 0) return Vector2(0, 1);
						else return Vector2(-1, 0);
					}
					else return Vector2(0, 1);
				}
				return Vector2(0, 1);
			}
			if (iright)
			{
				if (pos.x <= base.x) return Vector2(0, 1);
				if (pos.x <= (base.x + dim.x))
				{
					if (pos.y <= (base.y + dim.y))
					{
						if (dir.x <= 0) return Vector2(0, 1);
						else return Vector2(1, 0);
					}
					return Vector2(0, 1);
				}
				return Vector2(1, 0);
			}
			if (ibot)
			{
				if (pos.y >= base.y) 
				{
					if (pos.y <= (base.y + dim.y))
					{
						if (dir.y >= 0)
							return Vector2(0, 1);
						else
							return Vector2(0, -1);
					}
					return Vector2(0, 1);
				}
				else return Vector2(0, -1);
			}
		}
		if (ibot)
		{
			if (ileft)
			{
				if (pos.x <= base.x) return Vector2(-1, 0);
				if (pos.x <= (base.x + dim.x))
				{
					if (pos.y >= base.y)
					{
						if (dir.x <= 0) return Vector2(-1, 0);
						else return Vector2(0, -1);
					}
					return Vector2(0, -1);
				}
				return Vector2(0, -1);
			}
			if (iright)
			{
				if (pos.x <= base.x) return Vector2(0, -1);
				if (pos.x <= (base.x + dim.x))
				{
					if (pos.y >= base.y)
					{
						if (dir.x >= 0) return Vector2(1, 0);
						else return Vector2(0, -1);
					}
					return Vector2(0, -1);
				}
				return Vector2(1, 0);
			}
		}
		if (pos.x <= base.x) return Vector2(-1, 0);
		else 
		{
			if (pos.x < (base.x + dim.x))
			{
				if (dir.x <= 0)
					return Vector2(-1, 0);
				else
					return Vector2(1, 0);
			}
			return Vector2(1, 0);
		}
	}
	
	return Vector2(0, 0);
}

// ------------------------------------
Box Box::Translate( float x, float y)
// ------------------------------------
{
	return Box(Vector2(base.x + x, base.y + y), dim);
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
	
	/*
	printf("Segs: ");
	if (itop) printf("top ");
	if (ibot) printf("bot ");
	if (ileft) printf("left ");
	if (iright) printf("right ");
	printf("\n");
	*/
	
	if (ints == 1)
	{
		if (itop) return other.IntersectionPoint(top);
		if (ibot) return other.IntersectionPoint(bot);
		if (ileft) return other.IntersectionPoint(left);
		if (iright) return other.IntersectionPoint(right);
	}
	else
	{
		float sign = (other.pos.y - base.y) - (other.pos.x - base.x);
		float isign = (other.pos.y - base.y) + (other.pos.x - base.x);
		if (itop)
		{
			if (ileft)
			{
				if (other.pos.x <= base.x) return other.IntersectionPoint(left);
				if (other.pos.x <= (base.x + dim.x))
				{
					if (other.pos.y <= (base.y + dim.y))
					{
						printf("here\n");
						if (other.dir.x >= 0) return other.IntersectionPoint(top);
						else return other.IntersectionPoint(left);
					}
					else return other.IntersectionPoint(top);
				}
				return other.IntersectionPoint(top);
			}
			if (iright)
			{
				if (other.pos.x <= base.x) return other.IntersectionPoint(top);
				if (other.pos.x <= (base.x + dim.x))
				{
					if (other.pos.y <= (base.y + dim.y))
					{
						if (other.dir.x <= 0) return other.IntersectionPoint(top);
						else return other.IntersectionPoint(right);
					}
					return other.IntersectionPoint(top);
				}
				return other.IntersectionPoint(right);
			}
			if (ibot)
			{
				if (other.pos.y >= base.y) 
				{
					if (other.pos.y <= (base.y + dim.y))
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
					if (other.pos.y >= base.y)
					{
						if (other.dir.x <= 0) return other.IntersectionPoint(left);
						else return other.IntersectionPoint(bot);
					}
					return other.IntersectionPoint(bot);
				}
				return other.IntersectionPoint(bot);
			}
			if (iright)
			{
				if (other.pos.x <= base.x) return other.IntersectionPoint(bot);
				if (other.pos.x <= (base.x + dim.x))
				{
					if (other.pos.y >= base.y)
					{
						if (other.dir.x >= 0) return other.IntersectionPoint(right);
						else return other.IntersectionPoint(bot);
					}
					return other.IntersectionPoint(bot);
				}
				return other.IntersectionPoint(right);
			}
		}
		if (other.pos.x <= base.x) return other.IntersectionPoint(left);
		else 
		{
			if (other.pos.x < (base.x + dim.x))
			{
				if (other.dir.x <= 0)
					return other.IntersectionPoint(left);
				else
					return other.IntersectionPoint(right);
			}
			return other.IntersectionPoint(right);
		}
	}
	
	return Vector2(0, 0);
}

// ------------------------------------
Mesh::Mesh()
// ------------------------------------
{

}

// ------------------------------------
Mesh::Mesh(std::vector<Vector2 > points) :
// ------------------------------------
	points(points)
{

}

// ------------------------------------
Mesh::Mesh(Box b)
// ------------------------------------
{
	points.push_back( b.base);
	points.push_back( b.base + Vector2(0, b.dim.y));
	points.push_back( b.base + b.dim);
	points.push_back( b.base + Vector2(b.dim.x, 0));
}

// ------------------------------------
void Mesh::AddPoint(const Vector2& point)
// ------------------------------------
{
	std::vector<Vector2 >::iterator it;
	for (it = points.begin(); it != points.end(); it++)
	{
		if ((*it) == point)
			return;
	}
	points.push_back(point);
}

// ------------------------------------
int Mesh::Size()
// ------------------------------------
{
	return points.size();
}

// ------------------------------------
void Mesh::Print()
// ------------------------------------
{
	std::vector<Vector2 >::iterator it;
	for (it = points.begin(); it != points.end(); it++)
	{
		(*it).print();
		printf(" ");
	}
	printf("\n");
}

// ------------------------------------
void Mesh::Translate(const Vector2& other)
// ------------------------------------
{
	std::vector<Vector2 >::iterator it;
	for (it = points.begin(); it != points.end(); it++)
	{
		(*it).x += other.x;
		(*it).y += other.y;
	}
}

// ------------------------------------
Mesh Mesh::MeshTranslatedBy(const Vector2& other)
// ------------------------------------
{
	Mesh ret;
	std::vector<Vector2 >::iterator it;
	for (it = points.begin(); it != points.end(); it++)
	{
		ret.AddPoint( Vector2((*it).x + other.x, (*it).y + other.y));
	}
	return ret;
}

// ------------------------------------
Box Mesh::GetAABB()
// ------------------------------------
{
	float minx = FLT_MAX;
	float maxx = -FLT_MAX;
	float miny = FLT_MAX;
	float maxy = -FLT_MAX;
	
	std::vector<Vector2 >::iterator it;
	for (it = points.begin(); it != points.end(); it++)
	{
		Vector2 v = (*it);
		if (v.x < minx) minx = v.x;
		if (v.x > maxx) maxx = v.x;
		if (v.y < miny) miny = v.y;
		if (v.y > maxy) maxy = v.y;
	}
	
	return Box( Vector2(minx, miny), Vector2(maxx - minx, maxy - miny));
}

// ------------------------------------
Vector2 Mesh::GetFarthestPointInDirection(const Vector2& dir)
// ------------------------------------
{
	Vector2 max = Vector2(0, 0);
	float proj = -FLT_MAX;
	std::vector<Vector2 >::iterator it;
	for (it = points.begin(); it != points.end(); it++)
	{
		float d = (*it).dot(dir);
		if (d > proj)
		{
			proj = d;
			max = (*it);
		}
	}
	return max;
}

// ------------------------------------
Vector2 Mesh::Support(Mesh b, const Vector2& dir)
// ------------------------------------
{
	Vector2 pa = GetFarthestPointInDirection(dir);
	Vector2 pb = b.GetFarthestPointInDirection(dir.scale(-1));
	
	return pa - pb;
}

// ------------------------------------
int Mesh::Contains(const Vector2& p)
// ------------------------------------
{
	if (points.size() < 3) return false;
	
	std::vector<Vector2 > pts = points;
	pts.push_back(points[0]);
	
	int inside = 1;
	
	std::vector<Vector2 >::iterator it;
	for (it = pts.begin(); it != pts.end() - 1; it++)
	{
		// printf("P1: "); (*it).print(); 
		// printf(" P2: "); (*(it + 1)).print(); printf("\n");
		Segment2 s = Segment2( *it, *(it + 1));
		inside = inside && s.IsClockwise(p);
	}
	
	return inside;
}

// ------------------------------------
int Mesh::HasVertex(const Vector2& p)
// ------------------------------------
{
	std::vector<Vector2 >::iterator it;
	for (it = points.begin(); it != points.end(); it++)
	{
		if (p == *it) return true;
	}
	return false;
}

// ------------------------------------
void Mesh::GJKEnsureClockwise()
// ------------------------------------
{
	if (points.size() != 3)
		return;
	Segment2 s = Segment2(points[0], points[1]);
	if (!s.IsClockwise(points[2]))
	{
		Vector2 tmp = points[1];
		points[1] = points[2];
		points[2] = tmp;
	}
}

// ------------------------------------
void Mesh::GJKAddPoint(const Vector2& other)
// ------------------------------------
{
	AddPoint(other);
	if (points.size() == 4)
		points.erase(points.begin());
	GJKEnsureClockwise();
}

// ------------------------------------
Vector2 Mesh::GJKGetNextDirection()
// ------------------------------------
{
	if (points.size() == 2)
	{
		Vector2 d = points[1] - points[0];
		Vector2 dn = d.ClockwiseNormal();
		Vector2 ao = -points[0];
		if (dn.dot(ao) < 0)
			dn = -dn;
		return dn;			
	}
	else if (points.size() == 3)
	{
		Vector2 a = points[0];
		Vector2 b = points[1];
		Vector2 c = points[2];
		Vector2 ac = a - c;
		Vector2 bc = b - c;
		Vector2 co = -c;
		
		Vector2 n = ac.TripleProduct(bc);
		if (n.dot(co) > 0)
			return n;
		n = bc.TripleProduct(ac);
		if (n.dot(co) > 0)
			return n; 
	}
	return Vector2(-1, 0);
}

// ------------------------------------
int Mesh::GJK(Mesh b)
// ------------------------------------
{
	return GJK(b, Vector2(0, 1));
}

// ------------------------------------
int Mesh::GJK(Mesh b, const Vector2& dir)
// ------------------------------------
{
	Mesh simplex;
	simplex.GJKAddPoint( Support(b, dir));
	Vector2 d = dir.scale(-1);
	
	while (true)
	{
		Vector2 next = Support(b, d);
		if (next.dot(d) < 0) 
			return false;
		simplex.GJKAddPoint(next);
		if (simplex.Contains(Vector2(0, 0))) 
			return true;
		
		d = simplex.GJKGetNextDirection();
	}
}

// ------------------------------------
void Mesh::EPAAddPoint(Vector2 p, Vector2 toAdd)
// ------------------------------------
{
	if (!HasVertex(toAdd))
	{
		std::vector<Vector2 >::iterator it;
		for (it = points.begin(); it != points.end(); it++)
		{
			if ((*it) == p)
				points.insert(it+1, toAdd);
		}
	}
}

// ------------------------------------
Segment2 Mesh::EPAGetClosestEdge()
// ------------------------------------
{
	std::vector<Vector2 > pts = points;
	pts.push_back(points[0]);
	
	Segment2 cEdge;
	float cDist = FLT_MAX;
	
	std::vector<Vector2 >::iterator it;
	for (it = pts.begin(); it != pts.end() - 1; it++)
	{
		Segment2 s = Segment2( *it, *(it+1));
		Vector2 d = s.p2 - s.p1;
		Vector2 p1o = -s.p1;
		Vector2 n = p1o.TripleProduct(d).normalize();
		float dist = s.p1.dot(n);
		if (dist < cDist)
		{
			cDist = dist;
			cEdge = s;
		}
	}
	
	cEdge.distToOrigin = cDist;	
	return cEdge;
}

// ------------------------------------
std::pair<float, Vector2> Mesh::EPA(Mesh b)
// ------------------------------------
{
	Mesh simplex;
	simplex.GJKAddPoint( Support(b, Vector2(0, 1)));
	Vector2 d = Vector2(0, -1);
	
	while (true)
	{
		Vector2 next = Support(b, d);
		simplex.GJKAddPoint(next);
		if (simplex.Contains(Vector2(0, 0))) 
			break;
		
		d = simplex.GJKGetNextDirection();
	}
	
	int i = 0;
	float lastmin = FLT_MAX;
	Vector2 n;
	while (i < 100)
	{
		Segment2 s = simplex.EPAGetClosestEdge();
		n = s.Normal();
		Vector2 p = Support(b, n);
		
		float dist = p.dot(n);
		//printf("Dist: %f\n", dist);
		//printf("DistToOrigin: %f\n", s.distToOrigin);
		if (dist - s.distToOrigin < .1)
			return make_pair(dist, n);
			
		simplex.EPAAddPoint(s.p1, p);
		lastmin = s.distToOrigin;
		i++;
	}
	printf("EPA: past\n");
	return make_pair(lastmin, n);
}

// ------------------------------------
void Mesh::DistAddPoint(const Vector2& other)
// ------------------------------------
{
	AddPoint(other);
	if (points.size() == 3)
		points.erase(points.begin());
}

// ------------------------------------
float Mesh::Distance(Mesh other)
// ------------------------------------
{
	Mesh simplex;
	simplex.DistAddPoint( Support(other, Vector2(0, 1)));
	Vector2 d = Vector2(0, -1);
	
	while (true)
	{
		Vector2 next = Support(other, d);
	}
}
