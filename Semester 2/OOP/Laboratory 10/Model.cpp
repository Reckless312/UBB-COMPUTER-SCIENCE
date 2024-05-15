#include "Model.h"

void MyModel::addDog(const Dog& dog)
{
	this->dogs.push_back(dog);
	this->beginInsertRows(QModelIndex(), this->dogs.size() - 1, this->dogs.size() - 1);
	this->endInsertRows();
}

MyModel::MyModel(QObject* parent):QAbstractTableModel(parent)
{
}

int MyModel::rowCount(const QModelIndex& parent) const
{
	return this->dogs.size();
}

int MyModel::columnCount(const QModelIndex& parent) const
{
	return 3;
}

QVariant MyModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int col = index.column();
	if (role == Qt::DisplayRole)
	{
		if (col == 0)
		{
			return QString::fromStdString(this->dogs[row].GetName());
		}
		else if (col == 1)
		{
			return QString::fromStdString(this->dogs[row].GetBreed());
		}
		else if (col == 2)
		{
			return QString::fromStdString(std::to_string(this->dogs[row].GetAge()));
		}
	}
	return QVariant(); 
}
