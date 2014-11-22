#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Model/ProjectTree/tree.h"
#include "Model/ProjectTree/project.h"
#include "delegate.h"

#include <QFile>
#include <QInputDialog>

#include <iostream>
using namespace std;

namespace View
{
    MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        ui->competences->setModel(mFactory.getCompetences());
        ui->activites->setModel(mFactory.getActivites());
        ui->activites->setItemDelegate(new Delegate(this));

        ui->treeView->setModel(mFactory.getProjetTree());


        projectsMapper = new QDataWidgetMapper;
        projectsMapper->setModel(mFactory.getProjetTree());
        projectsMapper->addMapping(ui->name, 0);
        projectsMapper->setCurrentModelIndex(mFactory.getProjetTree()->index(0,0));

        connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
                this, &MainWindow::projectsTreeSelectionChange);

    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    void MainWindow::on_actionAjouterProjet_triggered(){
        bool ok;
        QString text = QInputDialog::getText(this, tr("nouveau projet"),
                                            tr("nom du nouveau projet :"), QLineEdit::Normal,
                                            "", &ok);
        if (ok && !text.isEmpty()){
            mFactory.getProjets()->insertRow(0);
            mFactory.getProjets()->setData(mFactory.getProjets()->index(0,0), text);
        }
    }

    void MainWindow::on_actionAjouterCompetence_triggered(){
        bool ok;
        QString text = QInputDialog::getText(this, tr("nouvelle competence"),
                                            tr("nom de la nouvelle competence :"), QLineEdit::Normal,
                                            "", &ok);
        if (ok && !text.isEmpty()){
            mFactory.getCompetences()->insertRow(0);
            mFactory.getCompetences()->setData(mFactory.getCompetences()->index(0,0), text);
        }
    }

    void MainWindow::on_actionAjouterActivites_triggered(){
        bool ok;
        QString text = QInputDialog::getText(this, tr("nouvelle activités"),
                                            tr("nom de la nouvelle activités :"), QLineEdit::Normal,
                                            "", &ok);
        if (ok && !text.isEmpty()){
            Model::TableModel::Model* act=mFactory.getActivites();
            act->insertRow(0);
            act->setData(act->index(0,0), text);
        }
    }

    void MainWindow::projectsTreeSelectionChange(const QItemSelection & selected,
                                                 const QItemSelection & deselected){
        Q_UNUSED(deselected);
        if(selected.indexes().size()==1){
            projectsMapper->setCurrentModelIndex(selected.indexes()[0]);
        }
    }

    void MainWindow::on_tabWidget_currentChanged(int index){
        if(index==0){
            ui->proprietes->setHidden(false);
        }else{
            ui->proprietes->setHidden(true);
        }
    }

    void MainWindow::on_inclureActivite_clicked(){
        QModelIndexList indexList=ui->treeView->selectionModel()->selectedIndexes();

        if(indexList.size()!=1){
            return;
        }

        Model::ProjectTree::Item* item=static_cast<Model::ProjectTree::Item*>(
                    indexList.at(0).internalPointer());

        Model::ProjectTree::Project* proj=
                dynamic_cast<Model::ProjectTree::Project*>(item);

        if(proj==NULL){
            return;
        }


    }
}
