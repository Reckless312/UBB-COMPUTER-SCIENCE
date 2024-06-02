#pragma once

#include <string>

using namespace std;

class Document
{
public:
	string name, keywords, content;
	Document() {};
	Document(string name, string keywords, string content);
	string GetName();
	string GetKeywords();
	string GetContent();
};