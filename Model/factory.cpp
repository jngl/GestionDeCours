#include "factory.h"

namespace Model
{
    Factory::Factory(QObject *parent) :
        QObject(parent)
    {
        //Competences
        TableModel::ModelMetadata md;
        md.add().setName("nom").setType(TableModel::Type_STRING);
        mCompetences = new TableModel::Model(md);

        //projets
        mProjets = new TableModel::Model(md);

        //activites
        md.add().setName("Competences").setType(TableModel::Type_FOREYGN_KEY).setForeignKey(mCompetences);
        mActivites = new TableModel::Model(md);

        //ActivitesProjets
        md.clear();
        md.add().setName("Activites").setType(TableModel::Type_FOREYGN_KEY).setForeignKey(mActivites);
        md.add().setName("Projets").setType(TableModel::Type_FOREYGN_KEY).setForeignKey(mProjets);
        mActivitesProjets = new TableModel::Model(md);

        mProjetTree = new ProjectTree::Tree(*mProjets, this);
    }

    Factory::~Factory(){
        delete mProjetTree;

        delete mCompetences;
        delete mActivites;
        delete mProjets;
    }

    TableModel::Model* Factory::getCompetences(){
        return mCompetences;
    }

    TableModel::Model* Factory::getProjets(){
        return mProjets;
    }

    TableModel::Model* Factory::getActivites(){
        return mActivites;
    }

    TableModel::Model* Factory::getActivitesProjets(){
        return mActivitesProjets;
    }

    ProjectTree::Tree* Factory::getProjetTree(){
        return mProjetTree;
    }
}
