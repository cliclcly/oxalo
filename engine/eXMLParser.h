// ****************************************************************************
// eXMLParser.h
// 
//
// ****************************************************************************

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>

// ------------------------------------
class XMLNode
// ------------------------------------
{
public:
	XMLNode();
	XMLNode(std::string);
	XMLNode * findChild(std::string);
	
	std::string m_title;
	std::vector<XMLNode*> m_children;
	std::string m_value;
	
	
};

// ------------------------------------
class XMLParser
// ------------------------------------
{
public:
	static XMLNode * Parse(std::string);
	static  void parseRecursive(XMLNode*, std::string&);
	static bool isStartTag(std::string);
	static bool isEndTag(std::string);
	static void Trim(std::string&);
};