#ifndef MODELROW_H
#define MODELROW_H

#include "modelmetadata.h"
#include "modelforeignkey.h"

#include <QVariant>
#include <QVector>
#include <QJsonValue>

namespace Model
{
    namespace TableModel
    {
        class ModelRow
        {
        public:
            ModelRow(ModelMetadata& metadata);

            bool set(int index, QVariant value);

            QVariant get(int index);

            bool isReferenced();

            void addReference();
            void deleteRefence();

            bool readJsonValue(QJsonValue value);
            bool readDateJsonValue(int index, QJsonValue value);
            bool readForeignKeyValue(int index, QJsonValue value);
            bool readIntJsonValue(int index, QJsonValue value);
            bool readStringJsonValue(int index, QJsonValue value);

        private:
            ModelMetadata& mMetadata;
            QVector<QVariant> mData;
            int mReferenceNumber;
        };
    }
}


#endif // MODELROW_H
