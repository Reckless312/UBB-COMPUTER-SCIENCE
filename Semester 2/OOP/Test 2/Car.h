#pragma once

#include "Engine.h"

class Car
{
private:
	string bodyStyle;
	Engine* engine;
public:
	Car(string bodyStyle, Engine* engine);
	string Getstyle();
	Engine* GetEngine();
	double computePrice();
};
