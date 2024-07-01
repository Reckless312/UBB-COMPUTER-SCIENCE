#include "Quiz.h"

std::vector<std::string> Quiz::tokenize(std::string str, char delimitator)
{
    std::stringstream ss(str);
    std::vector<std::string> result;
    std::string tok;
    while (std::getline(ss, tok, delimitator))
    {
        result.push_back(tok);
    }
    return result;
}

Quiz::~Quiz()
{
    for (Question* q : this->question)
    {
        delete q;
    }
}

std::vector<Question*> Quiz::getQuestions()
{
    return this->question;
}

void Quiz::add(int id, std::string text, std::string answer, int score)
{
    Question* question = new Question(id, text, answer, score);
    this->question.push_back(question);
}

std::istream& operator>>(std::istream& is, Quiz& quiz)
{
    std::string line;
    std::getline(is, line);
    std::vector<std::string> tok = quiz.tokenize(line, ',');
    if (tok.size() != 4)
    {
        return is;
    }
    Question* question = new Question(std::stoi(tok[0]), tok[1], tok[2], std::stoi(tok[3]));
    quiz.question.push_back(question);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Quiz& quiz)
{
    for (Question* q : quiz.question)
    {
        os << std::to_string(q->getId()) << "," << q->getText() << "," << q->getAnswer() << "," << std::to_string(q->getScore()) << "\n";
    }
    return os;
}
