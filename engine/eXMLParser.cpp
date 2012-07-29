// ****************************************************************************
// eXMLParser.cpp
// 
//
// ****************************************************************************

#include "eXMLParser.h"

// ------------------------------------
XMLNode::XMLNode()
// ------------------------------------
{

}

// ------------------------------------
XMLNode::XMLNode(std::string title):
// ------------------------------------
	m_title(title)
{

}

// ------------------------------------
XMLNode * XMLNode::findChild(std::string findTitle)
// ------------------------------------
{
	//printf("in node with title (%s) looking for (%s)\n",m_title.c_str(),findTitle.c_str());
	for(int i=0;i<m_children.size();i++)
	{
		//printf("looking at (%s)\n",m_children.at(i)->m_title.c_str());
		if (m_children.at(i)->m_title.compare(findTitle)==0)
		{
			return m_children.at(i);
		}
	}
	return NULL;
}

// ------------------------------------
XMLNode * XMLParser::Parse(std::string path)
// ------------------------------------
{
	XMLNode * base = new XMLNode();
	
	std::ifstream ifs(path.c_str());
  
    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	//printf("\n%s\n",content.c_str());
	
	//read of XML version (currently ignored)
	int pos = content.find_first_of("<");
	//printf("%d\n",pos);
	if (pos == -1){ throw new std::exception();}
	content.erase(0, pos+1);
	//printf("\n-----------------------\n%s\n",content.c_str());
	pos = content.find_first_of("?");
	//printf("%d\n",pos);
	if (pos!=0) { throw new std::exception();}
	content.erase(0,1);
	std::string temp = content.substr(0,content.find_first_of(">")+1);
	//printf("temp:%s\n",temp.c_str());
	XMLParser::Trim(temp);
	//printf("temptrimmed:%s\n",temp.c_str());
	if(temp.compare(std::string("xml version=\"1.0\"?>"))!=0) { throw new std::exception();}
	content.erase(0,content.find_first_of(">")+1);
	XMLParser::Trim(content);
	if(!XMLParser::isStartTag(content)) {throw new std::exception();}
	temp = content.substr(1,content.find_first_of(">")-1);
	XMLParser::Trim(temp);
	base->m_title = temp;
	//printf("base title: %s\n",temp.c_str());
	content.erase(0,content.find_first_of(">")+1);
	XMLParser::Trim(content);
	//printf("entering loop\n");
	while(content.size()!=0)
	{
		//printf("base loop start with:\n%s\n",content.c_str());
		if(XMLParser::isEndTag(content)){throw new std::exception();}
		if(!XMLParser::isStartTag(content))
		{
			//printf("is a value\n");
			std::string toBeValue = content.substr(0,content.find_first_of("<"));
			XMLParser::Trim(toBeValue);
			base->m_value =toBeValue;
			content.erase(0,content.find_first_of("<"));
			XMLParser::Trim(content);
			//printf("value of |%s|\n", base->m_value.c_str());
			if(!XMLParser::isEndTag(content)) {throw new std::exception();}
			//printf("followed by end tag\n");
			if(base->m_title.compare(content.substr(2,content.find_first_of(">")-2))!=0) {throw new std::exception();}
			//printf("end tag was base's: %s\n",content.substr(2,content.find_first_of(">")-2).c_str());
			content.erase(0,content.find_first_of(">")+1);
			XMLParser::Trim(content);
			return base;
		}
		else
		{
			//printf("has base start tag\n");
			temp = content.substr(1,content.find_first_of(">")-1);
			content.erase(0,content.find_first_of(">")+1);
			XMLParser::Trim(temp);
			XMLNode * child = new XMLNode(temp);
			base->m_children.push_back(child);
			//printf("enter recursive on %s\n",temp.c_str());
			XMLParser::Trim(content);
			XMLParser::parseRecursive(child,content);
			//printf("end recursion\n");
			XMLParser::Trim(content);
			if(XMLParser::isEndTag(content))
			{
				//printf("had end tag:|%s|\n",content.substr(2,content.find_first_of(">")-2).c_str());
				if(base->m_title.compare(content.substr(2,content.find_first_of(">")-2))!=0) {throw new std::exception();}
				//printf("had right end tag:%s\n",content.substr(2,content.find_first_of(">")-2).c_str());
				content.erase(0,content.find_first_of(">")+1);
				XMLParser::Trim(content);
				return base;
			}
		}
	}
	throw new std::exception();
}

// ------------------------------------
void XMLParser::parseRecursive(XMLNode* parent, std::string& toParse)
// ------------------------------------
{
	//printf("entering recursion on:\n%s\n",toParse.c_str());
	if(XMLParser::isEndTag(toParse)) {throw new std::exception();}
	//printf("rec: not end tag\n");
	if (XMLParser::isStartTag(toParse))
	{
		//printf("rec: has start tag\n");
		while(toParse.size()!=0)
		{
			//printf("rec:start loop with parent %s\n",parent->m_title.c_str());
			if(!XMLParser::isStartTag(toParse))
			{
				if (!XMLParser::isEndTag(toParse)){throw new std::exception();}
				return;
			}
			std::string temp = toParse.substr(1,toParse.find_first_of(">")-1);
			toParse.erase(0,toParse.find_first_of(">")+1);
			XMLParser::Trim(temp);
			
			//printf("rec: start tag: %s\n",temp.c_str());
			XMLNode * child = new XMLNode(temp);
			parent->m_children.push_back(child);
			XMLParser::Trim(toParse);
			XMLParser::parseRecursive(child,toParse);
			XMLParser::Trim(toParse);
			
			//printf("rec: end recursion\n");
			if(XMLParser::isEndTag(toParse))
			{
				//printf("rec: is end tag\n");
				if(parent->m_title.compare(toParse.substr(2,toParse.find_first_of(">")-2))!=0) 
				{
				//printf("rec: parent (%s) no match (%s)\n",parent->m_title.c_str(),toParse.substr(2,toParse.find_first_of(">")-2).c_str());
				throw new std::exception();
				}
				//printf("rec:mathes parent's title: %s\n",toParse.substr(2,toParse.find_first_of(">")-2).c_str());
				toParse.erase(0,toParse.find_first_of(">")+1);
				return;
			}
			XMLParser::Trim(toParse);
			//printf("rec:end loop\n");
		}
	}
	else if (toParse.find_first_of("<")!=-1){
		//printf("rec: is a value\n");
		std::string toBeValue = toParse.substr(0,toParse.find_first_of("<"));
		XMLParser::Trim(toBeValue);
		parent->m_value =toBeValue;
		toParse.erase(0,toParse.find_first_of("<"));
		XMLParser::Trim(toParse);
		//printf("rec: value of %s\n", parent->m_value.c_str());
		if(!XMLParser::isEndTag(toParse)) {throw new std::exception();}
		//printf("rec:followed by end tag\n");
		if(parent->m_title.compare(toParse.substr(2,toParse.find_first_of(">")-2))!=0) {throw new std::exception();}
		//printf("rec:end tag was parent's: %s\n",toParse.substr(2,toParse.find_first_of(">")-2).c_str());
		toParse.erase(0,toParse.find_first_of(">")+1);
		XMLParser::Trim(toParse);
	}else{throw new std::exception();}
}

// ------------------------------------
bool XMLParser::isStartTag(std::string tagCheck)
// ------------------------------------
{
	//printf("checking tag\ntag size:|%d|\nfirst char:|%s|\nsecond:|%s|\nfirst >: %d \n",
			//tagCheck.size(),tagCheck.substr(0,1).c_str(),tagCheck.substr(1,1).c_str(),tagCheck.find_first_of(">"));
	if (tagCheck.size()>2 && tagCheck.substr(0,1).compare(std::string("<"))==0 &&
		tagCheck.substr(1,1).compare(std::string("/"))!=0 && tagCheck.find_first_of(">")!=-1)
	{
		//printf("is long enough, starts with < and not </ and evenyually a >\n");
		std::string temp = tagCheck.substr(1,tagCheck.find_first_of(">")-1);
		//printf("using |%s|\n",temp.c_str());
		XMLParser::Trim(temp);
		if (temp.size()!=0)
		{
			return true;
		}
		return false;
	}
	return false;
}

// ------------------------------------
bool XMLParser::isEndTag(std::string tagCheck)
// ------------------------------------
{
	if (tagCheck.size()>3 && tagCheck.substr(0,1).compare(std::string("<"))==0 &&
		tagCheck.substr(1,1).compare(std::string("/"))==0 && tagCheck.find_first_of(">")!=-1)
	{
		XMLParser::Trim(tagCheck);
		if (tagCheck.find_first_of(">")>0)
		{
			return true;
		}
		return false;
	}
	return false;
}

// -----------------------------------==-
void XMLParser::Trim(std::string &trim)
// ------------------------------------
{
	trim.erase(trim.find_last_not_of(" \n\r\t")+1);
	size_t startpos = trim.find_first_not_of(" \n\r\t");
	if( std::string::npos != startpos )
	{
		trim = trim.substr( startpos );
	}
}
