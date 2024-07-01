#pragma once

#include <string>

class Question
{
private:
	int id;
	std::string text;
	std::string correct_answer;
	int score;
	
public:
	Question(int id, std::string text, std::string correct_answer, int score) { this->id = id, this->text = text, this->correct_answer = correct_answer, this->score = score; }

	int getId() { return this->id; }
	std::string getText() { return this->text; }
	std::string getAnswer() { return this->correct_answer; }
	int getScore() { return this->score; }
	
	std::string toStringFull();
	std::string toStringShort();
};