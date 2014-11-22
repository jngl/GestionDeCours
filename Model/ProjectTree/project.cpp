#include "project.h"

namespace Model
{
    namespace ProjectTree
    {
        Project::Project(TableModel::Model* projets, int id, Item *parent) :
            Item(parent),
            mProjets(projets),
            mId(id)
        {
        }

        QString Project::name(){
            return mProjets->data(mProjets->index(mProjets->rowIndexFromId(mId), 0)).toString();
        }

        int Project::id(){
            return mId;
        }
    }
}
