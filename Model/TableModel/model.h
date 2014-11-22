#ifndef MODEL_H
#define MODEL_H

#include "modelmetadata.h"
#include "modelrow.h"

#include <QAbstractTableModel>
#include <QMap>
#include <QVector>
#include <functional>
#include <QJsonValue>

namespace Model
{
    namespace TableModel
    {
        class Model : public QAbstractTableModel
        {
            Q_OBJECT
        public:
            Model(ModelMetadata metadata);
            ~Model();
            int rowCount(const QModelIndex & parent = QModelIndex()) const override;
            int columnCount(const QModelIndex & parent = QModelIndex()) const override;
            QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
            bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;
            Qt::ItemFlags flags(const QModelIndex & index) const override;
            bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex()) override;
            bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex()) override;

            QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole)const override;

            int id(int row);
            int rowIndexFromId(int i);

            ModelRow* rowFromId(int id);
            ModelRow* rowFromIndex(int index);

            QString getRowName(int id);
            void setRowNameFonction(std::function<QString(Model&, int)> func);

            ModelMetadata& getMetadata();

            bool readJsonValue(QJsonValue value);

        private:
            QVector< ModelRow* > mTable;
            QVector<int> mIds;
            int mIdMax;
            ModelMetadata mMetadata;
            std::function<QString(Model&, int)> mGetRowName;
        };
    }
}

#endif // MODEL_H
