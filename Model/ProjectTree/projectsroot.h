#ifndef MODELPROJECTSROOT_H
#define MODELPROJECTSROOT_H

#include "Model/ProjectTree/item.h"
#include "Model/TableModel/model.h"

namespace Model
{
    namespace ProjectTree
    {
        class Project;

        class ProjectsRoot : public Item
        {
            Q_OBJECT
        public:
            explicit ProjectsRoot();
            virtual ~ProjectsRoot();

            void addProject(TableModel::Model* projets, int id, int pos);

            QString name();

        private:
            QList<Project*> mProjects;

        };
    }
}

#endif // MODELPROJECTSROOT_H
