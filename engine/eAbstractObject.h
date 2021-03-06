// ****************************************************************************
// eAbstractObject.h
//
//
// ****************************************************************************

#ifndef __EABSTRACTOBJECT_H__
#define __EABSTRACTOBJECT_H__

#include "eMessage.h"
#include "eCamera.h"
#include "eAttribute.h"
#include "eComponent.h"
#include <vector>

// ------------------------------------
class AbstractObject : public iLoggable
// ------------------------------------
{
public:
	AbstractObject();
	
	virtual int RespondsTo(EMSG m) = 0;
	virtual void HandleMsg(Message* m);
	
	virtual int HasComponent(ECOMP c);
	virtual int AddComponent(ECOMP c);
	//virtual int AddComponent(Component* c);
	virtual Component* GetComponent(ECOMP c);
	
	virtual int HasAttribute(EATTR a);
	virtual Attribute* AddAttribute(EATTR a);
	virtual int AddAttribute(Attribute* );
	virtual Attribute* GetAttribute(EATTR a);
	
	virtual std::string Log(int fields[], int size);
	
	int GUID;
	
public:
	std::vector<Attribute* > m_attrs;
	std::vector<Component* > m_comps;
};

// ------------------------------------
class Square : public AbstractObject
// ------------------------------------
{
public:
	Square();
	Square(float x, float y);
	
	virtual int RespondsTo(EMSG m);
};

// ------------------------------------
class Triangle : public AbstractObject
// ------------------------------------
{
public:
	Triangle();
	Triangle(float x, float y);
	
	virtual int RespondsTo(EMSG m);
};

// ------------------------------------
class PSquare : public Square
// ------------------------------------
{
public:
	PSquare();
	PSquare(float x, float y);
	
	virtual int RespondsTo(EMSG m);
};

#endif
