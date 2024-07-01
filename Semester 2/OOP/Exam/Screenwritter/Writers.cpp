#include "Writers.h"
#include <sstream>
#include <fstream>

Writers::Writers(string name, string expertise, MyModel& model, QWidget *parent)
    : name(name), expertise(expertise), model(model), QWidget(parent)
{
    ui.setupUi(this);
    this->ui.tableView->setModel(&this->model);
    this->ui.tableView->resize(600, 500);
    this->ui.tableView->setColumnWidth(0, 100);
    this->ui.tableView->setColumnWidth(1, 200);
    this->ui.tableView->setColumnWidth(2, 100);
    this->ui.tableView->setColumnWidth(3, 100);
    QObject::connect(this->ui.pushButton, &QPushButton::clicked, this, &Writers::AddHandler);
    QObject::connect(this->ui.pushButton_2, &QPushButton::clicked, this, &Writers::AcceptHandler);
    QObject::connect(this->ui.pushButton_3, &QPushButton::clicked, this, &Writers::developHandler);
    QObject::connect(this->ui.pushButton_4, &QPushButton::clicked, this, &Writers::saveHandler);
    QObject::connect(this->ui.pushButton_5, &QPushButton::clicked, this, &Writers::plotHandler);
}

Writers::~Writers()
{}

vector<string> Writers::tokenize(string str, char delimitator)
{
    stringstream ss(str);
    vector<string> result;
    string line;
    while (getline(ss, line, delimitator))
    {
        result.push_back(line);
    }
    return result;
}

void Writers::AddHandler()
{
    QString description = this->ui.lineEdit->text(), act = this->ui.lineEdit_2->text();
    this->model.addIdea(description.toStdString(), "proposed", this->name, stoi(act.toStdString()));
}

void Writers::AcceptHandler()
{
    if (this->expertise != "Senior")
    {
        return;
    }
    QString description = this->ui.lineEdit->text(), act = this->ui.lineEdit_2->text();
    this->model.acceptIdea(description.toStdString(), stoi(act.toStdString()));
}

void Writers::developHandler()
{
    this->ui.textEdit->clear();
    vector<Idea> accepted = this->model.getAccepted(this->name);
    for (auto i : accepted)
    {
        this->ui.textEdit->append(QString::fromStdString(i.getDescription()));
    }
}

void Writers::saveHandler()
{
    QString text = this->ui.textEdit->toPlainText();
    string text_ = text.toStdString();
    stringstream ss(text_);
    string line;
    ofstream g(this->name + ".txt");
    while (getline(ss, line, '\n'))
    {
        g << line << '\n';
    }
    g.close();
}

void Writers::plotHandler()
{
    vector<Idea> accepted = this->model.getAllAccepted();
    sort(accepted.begin(), accepted.end(), [](Idea a, Idea b) {return a.getAct() < b.getAct(); });
    vector<Idea>::iterator it = accepted.begin();
    ofstream g("Plot.txt");
    for (int i = 0; i < 3; i++)
    {
        g << "ACT " << i + 1 << "\n";
        while (it != accepted.end() && it->getAct() == i + 1)
        {
            g << it->getDescription() + " (" + it->getCreator() + ")\n";
            it++;
        }
    }
    g.close();
}

std::istream& operator>>(istream& is, Writers& writer)
{
    string line;
    vector<string> tok;
    getline(is, line);
    tok = writer.tokenize(line, ',');
    if (tok.size() != 2)
    {
        return is;
    }
    writer.name = tok[0];
    writer.expertise = tok[1];
    return is;
}

std::ostream& operator<<(ostream& os, const Writers& writer)
{
    return os << writer.name << "," << writer.expertise << "\n";
}
