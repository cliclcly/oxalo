// ****************************************************************************
// iLoggable.h
//
//
// ****************************************************************************

#ifndef _ILOGGABLE_H_
#define _ILOGGABLE_H_

class iLoggable
{
public:
	virtual ~iLoggable() {}
	virtual std::string Log(int fields[],int size)=0;
};

#endif