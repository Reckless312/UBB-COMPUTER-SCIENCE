#include "Question.h"

std::string Question::toStringFull()
{
	return "ID: " + std::to_string(this->getId()) + " | Question: " + this->getText() + " | Answer: " + this->getAnswer() + " | Score: " + std::to_string(this->getScore()) + "\n";
}

std::string Question::toStringShort()
{
	return "ID: " + std::to_string(this->getId()) + " | Question: " + this->getText() + " | Score: " + std::to_string(this->getScore()) + "\n";
}
