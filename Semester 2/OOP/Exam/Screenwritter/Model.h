#pragma once

#include <qabstracttablemodel>
#include <Qtime>
#include "Idea.h"
#include <vector>

class MyModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit MyModel(QObject* parent = nullptr);
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	~MyModel();

private:
	vector<Idea*> plans;
	void reRead();
	
public:
	void Read();
	void addIdea(string description, string status, string creator, int act);
	void acceptIdea(string description, int act);
	vector<Idea> getAccepted(string name);
	vector<Idea> getAllAccepted();
};