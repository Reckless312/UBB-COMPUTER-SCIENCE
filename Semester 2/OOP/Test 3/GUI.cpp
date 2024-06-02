#include "GUI.h"

GUI::GUI(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    service.Call_Read();
    service.Sort();
    this->populate();
    QObject::connect(this->ui.lineEdit, &QLineEdit::textChanged, this, &GUI::searchhandler);
    QObject::connect(this->ui.pushButton, &QPushButton::clicked, this, &GUI::buttonhandler);
}

GUI::~GUI()
{}

void GUI::populate()
{
    this->ui.listWidget->clear();
    for (Document doc : this->service.Get_Doc())
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(doc.GetName() + " " + doc.GetKeywords()));
        this->ui.listWidget->addItem(item);
    }
}

void GUI::searchhandler()
{
    this->ui.listWidget->clear();
    QString line = this->ui.lineEdit->text();
    string line_ = line.toStdString();
    for (Document doc : this->service.Get_Doc())
    {
        if (doc.GetName().find(line_) != string::npos || doc.GetKeywords().find(line_) != string::npos)
        {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(doc.GetName() + " " + doc.GetKeywords()));
            this->ui.listWidget->addItem(item);
        }
    }
}

void GUI::buttonhandler()
{
    this->ui.listWidget->clear();
    QString line = this->ui.lineEdit->text();
    string line_ = line.toStdString();
    double max = 0;
    for (Document doc : this->service.Get_Doc())
    {
        if (doc.GetName().find(line_) != string::npos && max < (double)line_.size() / (double)doc.GetName().size())
        {
            this->ui.listWidget->clear();
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(doc.GetName() + " " + doc.GetKeywords()));
            this->ui.listWidget->addItem(item);
            max = (double)line_.size() / (double)doc.GetName().size();
        }
    }
}
