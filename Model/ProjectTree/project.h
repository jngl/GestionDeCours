#ifndef MODELPROJECT_H
#define MODELPROJECT_H

#include "Model/ProjectTree/item.h"
#include "Model/TableModel/model.h"

namespace Model
{
    namespace ProjectTree
    {
        class Project : public Item
        {
            Q_OBJECT
        public:
            explicit Project(TableModel::Model* projets, int id, Item *parent = 0);

            virtual QString name();

            int id();

        private:
            TableModel::Model* mProjets;
            int mId;
        };
    }
}

#endif // MODELPROJECTS_H
