#include "App.h"
#include <fstream>

void Application::readWriters()
{
	ifstream f("writers.txt");
	while (!f.eof())
	{
		Writers* w = new Writers("", "", *this->Model);
		f >> *w;
		this->writers.push_back(w);
		w->setWindowTitle(QString::fromStdString(w->getName()));
		w->show();
	}
	f.close();
}

Application::Application()
{
	this->readWriters();
}

Application::~Application()
{
	for (auto q : this->writers)
	{
		delete q;
	}
}
