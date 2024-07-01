#pragma once

#include <QtWidgets/QWidget>
#include "ui_Presenter.h"
#include "Observer.h"
#include "Quiz.h"
#include <algorithm>

class Presenter : public QWidget, public Observable
{
    Q_OBJECT

public:
    Presenter(Quiz& quiz, QWidget *parent = nullptr);
    ~Presenter();

private:
    Ui::PresenterClass ui;

private:
    Quiz& quiz;

    void populatelist();
    void addQuestion();
};
