#pragma once

#include <QAbstractTableModel>
#include "Idea.h"

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void Read();
    ~MyModel();
    void reRead();
    void addIdea(string title, string status, string creator, string description, int duration);
    string acceptIdea(string title, string description, int duration);
    vector<Idea> getAccepted(string name);
    void saveAllAccepted();
private:
    vector<Idea*> plans;
};