#include "Model.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <qmessagebox.h>

MyModel::MyModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    this->Read();
}

int MyModel::rowCount(const QModelIndex& /*parent*/) const
{
    return this->plans.size();
}

int MyModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 5;
}

QVariant MyModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int col = index.column();
    if (col == 0)
    {
        return QString::fromStdString(this->plans[row]->getTitle());
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
        return QString::fromStdString(this->plans[row]->getcreator());
    }
    else if (col == 4 )
    {
        return QString::fromStdString(to_string(this->plans[row]->getDuration()));
    }
}

void MyModel::Read()
{
    ifstream f("ideas.txt");
    while (!f.eof())
    {
        string line;
        getline(f, line);
        stringstream ss(line);
        vector<string> tok;
        string word;
        while (getline(ss, word, ','))
        {
            tok.push_back(word);
        }
        if (tok.size() == 5)
        {
            Idea* id = new Idea(tok[0], tok[1], tok[2], tok[3], stoi(tok[4]));
            this->plans.push_back(id);
        }
    }
    this->reRead();
}

MyModel::~MyModel()
{
    for (auto q : this->plans)
    {
        delete q;
    }
}

void MyModel::reRead()
{
    std::sort(this->plans.begin(), this->plans.end(), [](Idea* a, Idea* b) { return a->getDuration() < b->getDuration(); });
    this->beginInsertRows(QModelIndex(), this->plans.size() - 1, this->plans.size() - 1);
    this->endInsertRows();
}

void MyModel::addIdea(string title, string status, string creator, string description, int duration)
{
    Idea* id = new Idea(title, description, status, creator, duration);
    this->plans.push_back(id);
    this->reRead();
}

string MyModel::acceptIdea(string title, string description, int duration)
{
    for (auto q : this->plans)
    {
        if (q->getTitle() == title && q->getDescription() == description && q->getDuration() == duration)
        {
            if (q->getStatus() == "accepted")
            {
                return "Idea already accepted!";
            }
            q->setStatus();
            this->reRead();
            return "";
        }
    }
    return "Idea not found!";
}

vector<Idea> MyModel::getAccepted(string name)
{
    vector<Idea> id;
    for (auto q : this->plans)
    {
        if (q->getcreator() == name && q->getStatus() == "accepted")
        {
            id.push_back(*q);
        }
    }
    return id;
}

void MyModel::saveAllAccepted()
{
    ofstream g("acceptedideas.txt");
    vector<Idea> id;
    for (auto q : this->plans)
    {
        if (q->getStatus() == "accepted")
        {
            id.push_back(*q);
        }
    }
    for (auto q : id)
    {
        g << q.getTitle() << " (" << q.getcreator() << ") " << to_string(q.getDuration()) << " " << q.getDescription() << '\n';
    }
    g.close();
}

