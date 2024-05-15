#pragma once

#include <QDialog>
#include "ui_PopUp.h"

class PopUp : public QDialog
{
	Q_OBJECT

public:
	PopUp(QWidget *parent = nullptr);
	~PopUp();

private:
	Ui::PopUpClass ui;
};
