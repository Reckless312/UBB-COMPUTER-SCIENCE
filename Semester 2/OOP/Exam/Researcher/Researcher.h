#pragma once

#include <QtWidgets/QWidget>
#include "ui_Researcher.h"
#include <string>
#include "Model.h"
using namespace std;

class Researcher : public QWidget
{
    Q_OBJECT

public:
    Researcher(MyModel& model, string name, string position,QWidget *parent = nullptr);
    ~Researcher();
    void addHandler();
    void acceptHandler();
    void developHandler();
    void saveHandler();
    void updateHandler();
    void saveAllHandler();

private:
    Ui::ResearcherClass ui;
    string name;
    string position;
    MyModel& model;
};
