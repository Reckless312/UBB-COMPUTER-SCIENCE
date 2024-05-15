#include "PopUp.h"

PopUp::PopUp(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

PopUp::~PopUp()
{}

void PopUp::keyPressEvent(QKeyEvent * event)
{
	if (event->isAutoRepeat())
	{
		return;
	}
	this->keysPressed.insert(event->key());
	if (this->keysPressed.contains(Qt::Key_Control) && this->keysPressed.contains(Qt::Key_Z))
	{
		emit undoSignal();
	}
	else if (this->keysPressed.contains(Qt::Key_Control) && this->keysPressed.contains(Qt::Key_Y))
	{
		emit redoSignal();
	}
}

void PopUp::keyReleaseEvent(QKeyEvent* event)
{
	this->keysPressed.remove(event->key());
}


