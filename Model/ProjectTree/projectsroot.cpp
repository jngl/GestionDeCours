#include "projectsroot.h"

#include "project.h"

namespace Model
{
    namespace ProjectTree
    {
        ProjectsRoot::ProjectsRoot() :
            Item(NULL)
        {
        }
        ProjectsRoot::~ProjectsRoot(){
            while (!mProjects.isEmpty()){
                 delete mProjects.takeFirst();
            }
        }

        void ProjectsRoot::addProject(TableModel::Model* projets, int id, int pos){
            addChild(new Project(projets, id, this), pos);
        }

        QString ProjectsRoot::name(){
            return "Root";
        }
    }
}
