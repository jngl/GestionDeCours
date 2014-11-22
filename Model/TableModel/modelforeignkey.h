#ifndef MODELFOREIGNKEY_H
#define MODELFOREIGNKEY_H

#include <QString>
#include <QMetaType>

namespace Model
{
    namespace TableModel
    {
        class Model;

        class ModelForeignKey
        {
        public:
            ModelForeignKey(const ModelForeignKey& foreignKey);
            ModelForeignKey();
            ModelForeignKey(Model* model, int id=0);
            ~ModelForeignKey();

            void init(Model* model, int id=0);

            bool setId(int id);

            int getId()  const;
            Model* getModel() const;

            static bool isReferenced(Model* model, int id);

            ModelForeignKey& operator=(const ModelForeignKey& source);

        private:
            Model* mModel;
            int mId;//si = 0 pointeur null

            void addReference();
            void deleteReference();
        };
    }
}

Q_DECLARE_METATYPE(Model::TableModel::ModelForeignKey);

#endif // MODELFOREIGNKEY_H
