// ****************************************************************************
// iLoggable.cpp
//
//
// ****************************************************************************

#ifndef _ILOGGABLE_H_
#define _ILOGGABLE_H_

class iLoggable
{
public:
	virtual ~iLoggable() {}
	virtual std::string Log(int fields[]) const =0;
};

#endif