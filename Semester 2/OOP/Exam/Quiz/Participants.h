#pragma once

#include <QWidget>
#include "ui_Participants.h"
#include <sstream>
#include "Observer.h"
#include "Quiz.h"

class Participants : public QWidget, public Observer
{
	Q_OBJECT

public:
	Participants(Quiz& quiz, QWidget *parent = nullptr);
	~Participants();

private:
	Ui::ParticipantsClass ui;

private:
	std::string name;
	int score;
	Quiz& quiz;
	std::vector<Question> answered_corectly;
	std::vector<Question> answered_wrong;
	std::vector<Question> copy;

	std::vector<std::string> tokenize(std::string str, char delimitator);

public:
	friend std::istream& operator>>(std::istream& is, Participants& p);
	friend std::ostream& operator<<(std::ostream& os, const Participants& p);

	std::string getName();
	void update() override;

	void populatelist();
	void answer();
};
