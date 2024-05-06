#pragma once

#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Engine
{
protected:
	double basePrice;
public:
	virtual double getPrice() = 0;
	virtual string toString() = 0;
};

class ElectricEngine : public Engine
{
private:
	int autonomy;
public:
	ElectricEngine(int autonomy);
	double getPrice() override;
	string toString() override;
};

class TurboEngine : public Engine
{
public:
	TurboEngine();
	double getPrice() override;
	string toString() override;
};