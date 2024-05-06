#include "Car.h"

Car::Car(string bodyStyle, Engine* engine)
{
	this->bodyStyle = bodyStyle;
	this->engine = engine;
}

string Car::Getstyle()
{
	return this->bodyStyle;
}

Engine* Car::GetEngine()
{
	return this->engine;
}

double Car::computePrice()
{
	if (this->bodyStyle == "Sedan")
	{
		return 8000 + this->engine->getPrice();
	}
	else
	{
		return 9000 + this->engine->getPrice();
	}
}
