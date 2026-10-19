#pragma once
#include "service.h" 
#include <QAbstractTableModel>

class TableModel: public QAbstractTableModel {
private:
	Service& s;

	int countRank(int rank) const{
		const auto& toate = s.getAll();
		int k{0};
		for (const auto& m : toate) {
			if (m.getRank() == rank) {
				++k;
			}
		}
		return k;
	}
public:
	TableModel(Service& serv) : s{ serv } {

	}

	int rowCount(const QModelIndex& Parent = QModelIndex()) const override{
		return s.getAll().size();
	}

	int columnCount(const QModelIndex& Parent = QModelIndex()) const override {
		return 5;
	}

	QVariant data(const QModelIndex& index, int role) const override {
		

		const auto& toate = s.getAll();
		const auto&m = toate[index.row()];
		if(role == Qt::DisplayRole){
			if(index.column() == 0)
				return m.getId();
			else if(index.column() == 1)
					return QString::fromStdString(m.getTitlu());
			else if(index.column() == 2)
				return QString::fromStdString(m.getArtist());
			else if(index.column() == 3)
				return m.getRank();
			else if(index.column() == 4)
				return countRank(m.getRank());
		}
		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override{
		
		if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
		switch (section) {
			case 0: return "id";
			case 1: return "titlu";
			case 2: return "artist";
			case 3: return "rank";
			case 4: return "nr melodii cu acelasi rank";
			default: return QVariant();
		}
		return QVariant();
	}

	void refresh() {
		emit layoutAboutToBeChanged();
		emit layoutChanged();
	}
};