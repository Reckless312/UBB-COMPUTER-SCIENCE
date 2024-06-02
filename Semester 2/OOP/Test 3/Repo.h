#pragma once

#include <vector>

#include "Document.h"
#include <fstream>
#include <sstream>

class Repo
{
public:
	vector<Document> storage;
	void Read();
};
