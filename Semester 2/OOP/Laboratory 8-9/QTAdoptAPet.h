#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTAdoptAPet.h"

class QTAdoptAPet : public QMainWindow
{
    Q_OBJECT

public:
    QTAdoptAPet(QWidget *parent = nullptr);
    ~QTAdoptAPet();
private:
    Ui::QTAdoptAPetClass ui;
};
