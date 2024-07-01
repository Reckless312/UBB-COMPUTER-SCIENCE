#include "Researcher.h"
#include <sstream>
#include <fstream>
#include <qmessagebox.h>

Researcher::Researcher(MyModel& model, string name, string position, QWidget *parent)
    : model(model), QWidget(parent)
{
    ui.setupUi(this);
    this->name = name;
    this->position = position;
    this->setWindowTitle(QString::fromStdString(this->name));
    this->resize(1200, 500);
    this->ui.tableView->setModel(&this->model);
    if (this->position != "senior")
    {
        this->ui.pushButton_2->hide();
        this->ui.pushButton_5->hide();
    }
    QObject::connect(this->ui.pushButton, &QPushButton::clicked, this, &Researcher::addHandler);
    QObject::connect(this->ui.pushButton_2, &QPushButton::clicked, this, &Researcher::acceptHandler);
    QObject::connect(this->ui.pushButton_3, &QPushButton::clicked, this, &Researcher::developHandler);
    QObject::connect(this->ui.pushButton_4, &QPushButton::clicked, this, &Researcher::saveHandler);
    QObject::connect(this->ui.pushButton_6, &QPushButton::clicked, this, &Researcher::updateHandler);
    QObject::connect(this->ui.pushButton_5, &QPushButton::clicked, this, &Researcher::saveAllHandler);
}

Researcher::~Researcher()
{}

void Researcher::addHandler()
{
    QString title = this->ui.lineEdit->text(), description = this->ui.lineEdit_2->text(), duration = this->ui.lineEdit_3->text();
    if (title.toStdString() == "")
    {
        QMessageBox::warning(this, "Error", "Empty string inserted");
        return;
    }
    if (!(duration.toStdString() == "1" || duration.toStdString() == "2" || duration.toStdString() == "3"))
    {
        QMessageBox::warning(this, "Error", "Invalid duration");
        return;
    }
    this->model.addIdea(title.toStdString(), "proposed", this->name, description.toStdString(), stoi(duration.toStdString()));
}

void Researcher::acceptHandler()
{
    QString title = this->ui.lineEdit->text(), description = this->ui.lineEdit_2->text(), duration = this->ui.lineEdit_3->text();
    string error = this->model.acceptIdea(title.toStdString(), description.toStdString(), stoi(duration.toStdString()));
    if (error != "")
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(error));
    }
}

void Researcher::developHandler()
{
    vector<Idea> accepted = this->model.getAccepted(this->name);
    this->ui.listWidget->clear();
    for (auto id : accepted)
    {
        this->ui.listWidget->addItem(QString::fromStdString(id.getTitle() + ": " + id.getDescription()) + '\n');
    }
}

void Researcher::saveHandler()
{
    int count = this->ui.listWidget->count();
    for (int i = 0; i < count; i++)
    {
        if (this->ui.listWidget->item(i)->isSelected())
        {
            QString text = this->ui.listWidget->item(i)->text();
            stringstream ss(text.toStdString());
            string title;
            getline(ss, title, ':');
            string description;
            getline(ss, description);
            ofstream g(title + ".txt");
            g << description;
            g.close();
        }
    }
}

void Researcher::updateHandler()
{
    QString updated = this->ui.lineEdit_4->text();
    int count = this->ui.listWidget->count();
    for (int i = 0; i < count; i++)
    {
        if (this->ui.listWidget->item(i)->isSelected())
        {
            QString before = this->ui.listWidget->item(i)->text();
            stringstream ss(before.toStdString());
            string title;
            getline(ss, title, ':');
            this->ui.listWidget->item(i)->setText(QString::fromStdString(title) + ": " + updated + '\n');
            break;
        }
    }
}

void Researcher::saveAllHandler()
{
    this->model.saveAllAccepted();
}
