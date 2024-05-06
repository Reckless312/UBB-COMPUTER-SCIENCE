#include "Engine.h"

ElectricEngine::ElectricEngine(int autonomy)
{
	this->autonomy = autonomy;
	this->basePrice = 3000 + autonomy * 0.01;
}

double ElectricEngine::getPrice()
{
	return this->basePrice;
}

string ElectricEngine::toString()
{
	return "Type: Electric Engine, with autonomy: " + to_string(this->autonomy) + " and a price of: " + to_string(this->basePrice);
}

TurboEngine::TurboEngine()
{
	this->basePrice = 3000 + 100;
}

double TurboEngine::getPrice()
{
	return this->basePrice;
}

string TurboEngine::toString()
{
	return "Type: Turbo Engine with a price: " + to_string(this->basePrice);
}
