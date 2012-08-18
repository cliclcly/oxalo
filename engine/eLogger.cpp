// ****************************************************************************
// eLogger.cpp
//
//
// ****************************************************************************

#include "eLogger.h"
#include <time.h>
#include <stdio.h>

// ********************************************************
// Logger Statics
// ********************************************************

Logger* Logger::m_pInstance = NULL;

// ------------------------------------
Logger* Logger::Instance()
// ------------------------------------
{
	return m_pInstance;
}

// ------------------------------------
int Logger::Initialize(int level)
// ------------------------------------
{
	if (m_pInstance) return 0;
	
	m_pInstance = new Logger();
	int result = m_pInstance->initialize(level);
	return result;
}

// ------------------------------------
void Logger::Log(int level, std::string toLog)
// ------------------------------------
{
	if (!Instance()) return;
	
	Instance()->log(level, toLog);
}

// ------------------------------------
void Logger::Log(int level, iLoggable* toLog,int fields[])
// ------------------------------------
{
	if (!Instance()) return;
	
	Instance()->log(level,toLog->Log(fields));
}

// ------------------------------------
Logger::Logger()
// ------------------------------------
{
	
}

// ------------------------------------
Logger::~Logger()
// ------------------------------------
{

}

// ------------------------------------
int Logger::initialize(int level)
// ------------------------------------
{
	m_loggingLevel=level;
	time_t now;
	char the_date[12];

	the_date[0] = '\0';

	now = time(NULL);

	if (now != -1)
	{
		strftime(the_date, 20, "%Y_%m_%d_%H_%M_%S", gmtime(&now));
	}
	m_path = "Logs\\";
	m_path+= the_date;
	m_path+="-log.txt";
	m_logFile.open(m_path.c_str(),std::fstream::out);
	if(!m_logFile)
	{
		printf("Logging Initialize Failure\n");
	}
	m_logFile<<"Logging Begun\n";
	std::flush(m_logFile);
}

// ------------------------------------
void Logger::log(int level, std::string toLog)
// ------------------------------------
{
	if(level<m_loggingLevel) return;
	if(m_logFile.is_open())
	{
		m_logFile<<toLog;
		m_logFile<<"\n";
		std::flush(m_logFile);
	}else{
		printf("Logging Failure: %s\n", toLog.c_str());
	}
}

