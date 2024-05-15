#pragma once

#include <Qabstracttablemodel>
#include <Qtime>
#include <Dog.h>
#include <vector>
class MyModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	void addDog(const Dog& dog);
	explicit MyModel(QObject* parent = nullptr);
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
private:
	std::vector<Dog> dogs;


};