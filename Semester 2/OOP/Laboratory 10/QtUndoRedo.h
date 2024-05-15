#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtUndoRedo.h"

class QtUndoRedo : public QMainWindow
{
    Q_OBJECT

public:
    QtUndoRedo(QWidget *parent = nullptr);
    ~QtUndoRedo();

private:
    Ui::QtUndoRedoClass ui;
};
