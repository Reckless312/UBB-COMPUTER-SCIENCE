#include "Observer.h"

void Observable::add_observer(Observer* obs)
{
	this->observers.push_back(obs);
}

void Observable::notify()
{
	for (auto obs : this->observers)
	{
		obs->update();
	}
}
