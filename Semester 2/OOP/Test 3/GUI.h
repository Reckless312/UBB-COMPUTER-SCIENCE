#pragma once

#include <QtWidgets/QWidget>
#include "ui_GUI.h"
#include "Service.h"

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();
    Service service;
    void populate();
    void searchhandler();
    void buttonhandler();

private:
    Ui::GUIClass ui;
};
