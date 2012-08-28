// ****************************************************************************
// eLogger.cpp
//
//
// ****************************************************************************

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include <iostream>
#include <fstream>
#include "iLoggable.h"

class Logger
{
public:
	static Logger* Instance();
	static int Initialize(int level);
	static void Log(int level,std::string);
	static void Log(int level,iLoggable*,int fields[], int size);
	
public:
	int initialize(int level);
	void log(int level,std::string);
	
private:
	Logger();
	~Logger();
	
	static Logger* m_pInstance;
	std::fstream m_logFile;
	std::string m_path;
	int m_loggingLevel;
};

#endif