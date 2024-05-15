#pragma once

#include <QDialog>
#include "ui_PopUp.h"
#include <QKeyEvent>
#include <qset.h>
class GUI;
class PopUp : public QDialog
{
	Q_OBJECT
public:
	PopUp(QWidget *parent = nullptr);
	~PopUp();
	friend class GUI;
protected:
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	QSet<int> keysPressed;
signals:
	void undoSignal();
	void redoSignal();
private:
	Ui::PopUpClass ui;
};
