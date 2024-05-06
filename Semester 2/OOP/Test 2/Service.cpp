#include "Service.h"

void Service::addCar(string bodyStyle, string engineType, int autonomy)
{
	if (engineType == "Electric")
	{
		ElectricEngine* engine = new ElectricEngine(autonomy);
		Car car(bodyStyle, engine);
		this->repo.push_back(car);
	}
	else
	{
		TurboEngine* engine = new TurboEngine;
		Car car(bodyStyle, engine);
		this->repo.push_back(car);
	}
}

vector<Car> Service::ShowCars()
{
	return this->repo;
}

vector<Car> Service::getCarsWithMaxPrice(double maxPrice)
{
	vector<Car> cars;
	for (Car car : this->repo)
	{
		if (car.computePrice() < maxPrice)
		{
			cars.push_back(car);
		}
	}
	for (int i = 0; i < cars.size() - 1; i++)
	{
		for (int j = i + 1; j < cars.size(); j++)
		{
			if (cars[i].computePrice() > cars[j].computePrice())
			{
				Car carr = cars[i];
				cars[i] = cars[j];
				cars[j] = carr;
			}
		}
	}
	return cars;
}

void Service::writeToFile(string filename, vector<Car> cars)
{
	ofstream f(filename);
	for (Car car : cars)
	{
		Engine* eng = car.GetEngine();
		f << "Car with style: " << car.Getstyle() << " with a price: " << car.computePrice() << " | " << eng->toString() << endl;
	}
	f.close();
}
