#include "App.h"

Application::Application()
{
	this->populateQuiz();
	this->populateParticipants();
	this->StartParticipants();
	this->presenter = new Presenter(this->quiz);
	this->addObservers();
	this->presenter->show();
	this->presenter->notify();
}

Application::~Application()
{
	for (Participants* p : this->participants)
	{
		delete p;
	}
	delete this->presenter;
}

void Application::populateParticipants()
{
	std::ifstream f("participants.txt");
	if (!f.is_open())
	{
		return;
	}
	while (!f.eof())
	{
		Participants* p = new Participants(this->quiz);
		f >> *p;
		p->populatelist();
		this->participants.push_back(p);
	}
	f.close();
}

void Application::StartParticipants()
{
	for (Participants* p : this->participants)
	{
		p->setWindowTitle(QString::fromStdString(p->getName()));
		p->show();
	}
}

void Application::populateQuiz()
{
	std::ifstream f("questions.txt");
	if (!f.is_open())
	{
		return;
	}
	while (!f.eof())
	{
		f >> this->quiz;
	}
}

void Application::addObservers()
{
	for (auto q : this->participants)
	{
		this->presenter->add_observer(q);
	}
}
