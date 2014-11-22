#ifndef MODELMETADATA_H
#define MODELMETADATA_H

#include <QString>
#include <QList>

namespace Model
{
    namespace TableModel
    {
        class Model;

        enum Type{
            Type_INT,
            Type_STRING,
            Type_FOREYGN_KEY,
            Type_DATE
        };

        class ModelMetadataColumn{
        public:
            ModelMetadataColumn& setName(QString n);
            ModelMetadataColumn& setType(Type t);
            ModelMetadataColumn& setForeignKey(Model* fk);

            QString getName() const;
            Type getType() const;
            Model* getForeignKey() const;

        private:
            QString mName;
            Type mType;
            Model* mForeignKey;
        };

        class ModelMetadata{
        public:
            ModelMetadataColumn& add();

            int size() const;

            ModelMetadataColumn& get(int index);

            const ModelMetadataColumn& get(int index) const;

            void clear();

        private:
            QList<ModelMetadataColumn> mColumns;
        };
    }
}
#endif // MODELMETADATA_H
