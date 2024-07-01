#pragma once

#include <vector>
#include "Question.h"
#include "sstream"

class Quiz
{
private:
	std::vector<Question*> question;

	std::vector<std::string> tokenize(std::string str, char delimitator);

public:
	Quiz() { question = std::vector<Question*>(); }
	~Quiz();

	std::vector<Question*> getQuestions();

	friend std::istream& operator>>(std::istream& is, Quiz& quiz);
	friend std::ostream& operator<<(std::ostream& os, const Quiz& quiz);

	void add(int id, std::string text, std::string answer, int score);
};