#pragma once

#include <QtWidgets/QWidget>
#include "ui_Writers.h"
#include <vector>
#include "Model.h"
#include <qtableview.h>

using namespace std;

class Writers : public QWidget
{
    Q_OBJECT

public:
    Writers(string name, string expertise, MyModel& model, QWidget *parent = nullptr);
    ~Writers();

private:
    Ui::WritersClass ui;

private:
    string name, expertise;
    QTableView tableview;
    MyModel& model;

    vector<string> tokenize(string str, char delimitator);

    friend std::istream& operator>>(istream& is, Writers& writer);
    friend std::ostream& operator<<(ostream& os, const Writers& writer);

public:
    string getName() { return this->name; }

private:
    void AddHandler();
    void AcceptHandler();
    void developHandler();
    void saveHandler();
    void plotHandler();
};
