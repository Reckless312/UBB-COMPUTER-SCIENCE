#include "Document.h"

Document::Document(string name, string keywords, string content)
{
	this->name = name;
	this->keywords = keywords;
	this->content = content;
}

string Document::GetName()
{
	return this->name;
}

string Document::GetKeywords()
{
	return this->keywords;
}

string Document::GetContent()
{
	return this->content;
}
