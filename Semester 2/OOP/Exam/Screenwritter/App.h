#pragma once
#include "Writers.h"
#include <vector>

class Application
{
private:
	vector<Writers*> writers;
	MyModel* Model = new MyModel;
	void readWriters();

public:
	Application();
	~Application();
};