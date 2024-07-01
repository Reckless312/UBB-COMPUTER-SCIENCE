#pragma once

#include "Participants.h"
#include "Presenter.h"
#include "fstream"

class Application
{
private:
	Quiz quiz;
	Presenter* presenter;
	std::vector<Participants*> participants;

public:
	Application();
	~Application();

private:
	void populateParticipants();
	void StartParticipants();
	void populateQuiz();
	void addObservers();
};