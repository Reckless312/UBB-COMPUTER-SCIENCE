#pragma once

#include "Car.h"

class Service
{
private:
	vector<Car> repo;
public:
	void addCar(string bodyStyle, string engineType, int autonomy=0);
	vector<Car> ShowCars();
	vector<Car> getCarsWithMaxPrice(double maxPrice);
	void writeToFile(string filename, vector<Car> cars);
};