#include "Model.h"
#include <fstream>

MyModel::MyModel(QObject* parent)
{
	this->Read();
}

int MyModel::rowCount(const QModelIndex& parent) const
{
	return this->plans.size();
}

int MyModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant MyModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int col = index.column();
	if (col == 0)
	{
		return QString::fromStdString(this->plans[row]->getCreator());
	}
	else if (col == 1)
	{
		return QString::fromStdString(this->plans[row]->getDescription());
	}
	else if (col == 2)
	{
		return QString::fromStdString(this->plans[row]->getStatus());
	}
	else if (col == 3)
	{
		return QString::fromStdString(to_string(this->plans[row]->getAct()));
	}
}

MyModel::~MyModel()
{
	for (auto i : this->plans)
	{
		delete i;
	}
}

void MyModel::reRead()
{
	this->beginInsertRows(QModelIndex(), this->plans.size() - 1, this->plans.size() - 1);
	this->endInsertRows();
}

void MyModel::Read()
{
	ifstream f("ideas.txt");
	while (!f.eof())
	{
		Idea* i = new Idea("", "", "", 0);
		f >> *i;
		this->plans.push_back(i);
	}
	f.close();
}

void MyModel::addIdea(string description, string status, string creator, int act)
{
	if (description == "" || !(act == 1 || act == 2 || act == 3))
	{
		return;
	}
	for (auto q : this->plans)
	{
		if (q->getDescription() == description && q->getAct() == act)
		{
			return;
		}
	}
	Idea* i = new Idea(description, status, creator, act);
	this->plans.push_back(i);
	this->reRead();
}

void MyModel::acceptIdea(string description, int act)
{
	for (auto q : this->plans)
	{
		if (q->getDescription() == description && q->getAct() == act && q->getStatus() =="proposed")
		{
			q->setApproved();
			this->reRead();
			return;
		}
	}
}

vector<Idea> MyModel::getAccepted(string name)
{
	vector<Idea> result;
	for (auto q : this->plans)
	{
		if (q->getCreator() == name && q->getStatus() == "accepted")
		{
			result.push_back(*q);
		}
	}
	return result;
}

vector<Idea> MyModel::getAllAccepted()
{
	vector<Idea> result;
	for (auto q : this->plans)
	{
		if(q->getStatus() == "accepted")
		{
			result.push_back(*q);
		}
	}
	return result;
}
