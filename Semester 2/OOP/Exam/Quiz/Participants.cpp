#include "Participants.h"

Participants::Participants(Quiz& quiz, QWidget* parent)
	: quiz(quiz), QWidget(parent), name(""), score(-1)
{
	ui.setupUi(this);
	this->populatelist();
	QObject::connect(this->ui.pushButton, &QPushButton::clicked, this, &Participants::answer);
}

Participants::~Participants()
{}

std::vector<std::string> Participants::tokenize(std::string str, char delimitator)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimitator))
	{
		result.push_back(token);
	}
	return result;
}

std::string Participants::getName()
{
	return this->name;
}

void Participants::update()
{
	this->copy.clear();
	for (Question* q : this->quiz.getQuestions())
	{
		this->copy.push_back(*q);
	}
	std::sort(this->copy.begin(), this->copy.end(), [](Question a, Question b) {return a.getScore() > b.getScore(); });
	this->populatelist();
}

void Participants::populatelist()
{
	this->ui.listWidget->clear();
	for (Question q : copy)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(q.toStringShort()));
		for (auto q2 : this->answered_corectly)
		{
			if (q.getId() == q2.getId())
			{
				item->setBackground(Qt::green);
				break;
			}
		}
		for (auto q2 : this->answered_wrong)
		{
			if (q.getId() == q2.getId())
			{
				item->setBackground(Qt::red);
				break;
			}
		}
		this->ui.listWidget->addItem(item);
	}
	this->ui.lineEdit_2->setText(QString::fromStdString(std::to_string(this->score)));
}

void Participants::answer()
{
	for (int i = 0, count = this->ui.listWidget->count(); i < count; i++)
	{
		QListWidgetItem* item = this->ui.listWidget->item(i);
		if (item->isSelected())
		{
			Question q = this->copy[i];
			bool found = false;
			for (auto q2 : this->answered_corectly)
			{
				if (q2.getId() == q.getId())
				{
					found = true;
					break;
				}
			}
			if (found == true)
			{
				break;
			}
			for (auto q2 : this->answered_wrong)
			{
				if (q2.getId() == q.getId())
				{
					found = true;
					break;
				}
			}
			if (found == true)
			{
				break;
			}
			QString answer = this->ui.lineEdit->text();
			if (answer.toStdString() == q.getAnswer())
			{
				this->answered_corectly.push_back(q);
				this->score += q.getScore();
			}
			else
			{
				this->answered_wrong.push_back(q);
			}
			this->populatelist();
			break;
		}
	}
}

std::istream& operator>>(std::istream& is, Participants& p)
{
	std::string line;
	std::getline(is, line);
	std::vector<std::string> tokens = p.tokenize(line, ',');
	if (tokens.size() != 2)
	{
		return is;
	}
	p.name = tokens[0];
	p.score = std::stoi(tokens[1]);
	return is;
}

std::ostream& operator<<(std::ostream& os, const Participants& p)
{
	os << p.name << "," << std::to_string(p.score) << "\n";
	return os;
}
