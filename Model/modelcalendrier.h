#ifndef MODELCALENDRIER_H
#define MODELCALENDRIER_H

#include <QAbstractTableModel>

#include "TableModel/model.h"

namespace Model
{
    class ModelFactory;
/*
    class ModelCalendrier : public QAbstractTableModel
    {
        Q_OBJECT
    public:
        ModelCalendrier(ModelFactory& parent);

        int rowCount(const QModelIndex & parent = QModelIndex()) const override;
        int columnCount(const QModelIndex & parent = QModelIndex()) const override;
        QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
        bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;
        Qt::ItemFlags flags(const QModelIndex & index) const override;
        bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex()) override;
        bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex()) override;
        bool insertColumns(int col, int count, const QModelIndex & parent = QModelIndex()) override;
        bool removeColumns(int col, int count, const QModelIndex & parent = QModelIndex()) override;
        QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole)const override;

        int getYear();
        int getMonth();

        bool stage(int day) const;
        bool vacances(int day) const;
        bool CCF(int day) const;
        bool projet(int day, int projetIndex) const;

    public slots:
        void setYear(int year);
        void setMonth(int month);
        void updateProjet();

    private:
        ModelFactory& mFactory;
        TableModel::Model& mDateProjet;

        int mYear;
        int mMonth;//1=janvier
        int mNumberOfDay;
        int mNumberOfProjets;

        void update();

    };*/
}

#endif // MODELCALENDRIER_H
