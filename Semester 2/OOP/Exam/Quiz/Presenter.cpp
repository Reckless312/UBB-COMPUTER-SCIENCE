#include "Presenter.h"
#include "qmessagebox.h"

Presenter::Presenter(Quiz& quiz, QWidget* parent)
    : QWidget(parent), quiz(quiz)
{
    ui.setupUi(this);
    this->populatelist();
    QObject::connect(this->ui.pushButton, &QPushButton::clicked, this, &Presenter::addQuestion);
}

Presenter::~Presenter()
{}

void Presenter::populatelist()
{
    this->ui.listWidget->clear();
    std::vector<Question> copy;
    for (Question* q : this->quiz.getQuestions())
    {
        copy.push_back(*q);
    }
    std::sort(copy.begin(), copy.end(), [](Question a, Question b) {return a.getId() < b.getId(); });
    for (Question q : copy)
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(q.toStringFull()));
        this->ui.listWidget->addItem(item);
    }
}

void Presenter::addQuestion()
{
    QString id = this->ui.lineEdit->text(), question = this->ui.lineEdit_2->text(), answer = this->ui.lineEdit_3->text(), score = this->ui.lineEdit_4->text();
    std::string id_ = id.toStdString(), question_ = question.toStdString(), answer_ = answer.toStdString(), score_ = score.toStdString();
    if (question_ == "")
    {
        QMessageBox::critical(0, "Error", "Empty text!");
        return;
    }
    for (auto q : this->quiz.getQuestions())
    {
        if (q->getId() == std::stoi(id_))
        {
            QMessageBox::critical(0, "Error", "Question already exists!");
            return;
        }
    }
    this->quiz.add(std::stoi(id_), question_, answer_, std::stoi(score_));
    this->populatelist();
    this->notify();
}
