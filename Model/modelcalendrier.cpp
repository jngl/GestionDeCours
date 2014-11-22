#include "modelcalendrier.h"

#include "TableModel/modelforeignkey.h"

#include <QDate>
#include <QBrush>

#include <iostream>
using namespace std;

namespace Model
{/*
    ModelCalendrier::ModelCalendrier(ModelFactory& parent):
        QAbstractTableModel((QObject*)&parent),
        mFactory(parent),
        mDateProjet(mFactory.getModel("DateProjets")),
        mYear(2014),
        mMonth(1),
        mNumberOfDay(0),
        mNumberOfProjets(0)
    {
        QDate date=QDate::currentDate();
        mYear=date.year();
        mMonth=date.month();
        insertColumns(0, -1);
    }

    int ModelCalendrier::rowCount(const QModelIndex & /*parent*//* ) const {
        return mNumberOfProjets;
    }

    int ModelCalendrier::columnCount(const QModelIndex & /*parent*//*) const{
        return mNumberOfDay;
    }

    QVariant ModelCalendrier::data(const QModelIndex & index, int role ) const{
        if(role==Qt::DisplayRole){
            return tr("");
        }

        if(index.column()<0 ||
                index.column()>=mNumberOfDay ||
                index.row()<0 ||
                index.row()>=mNumberOfProjets){
            return QVariant();
        }

        if(vacances(index.column()+1)){
            if(role==Qt::BackgroundRole){
                return QVariant(QBrush(QColor(0,255,0)));
            }else{
                return QVariant();
            }
        }

        if(stage(index.column()+1)){
            if(role==Qt::BackgroundRole){
                return QVariant(QBrush(QColor(0,0,255)));
            }else{
                return QVariant();
            }
        }

        if(CCF(index.column()+1)){
            if(role==Qt::BackgroundRole){
                return QVariant(QBrush(QColor(255,0,0)));
            }else{
                return QVariant();
            }
        }

        bool value=projet(index.column()+1, index.row());

        if(role==Qt::EditRole){
            return QVariant(value);
        }else if(role==Qt::CheckStateRole){
            if(value){
                return QVariant(Qt::Checked);
            }else{
                return QVariant(Qt::Unchecked);
            }
        }else if(role==Qt::BackgroundRole){
            if(value){
                return QVariant(QBrush(QColor(0,0,0)));
            }else{
                return QVariant(QBrush(QColor(255,255,255)));
            }
        }else{
            return QVariant();
        }
    }

    bool ModelCalendrier::setData(const QModelIndex & index, const QVariant &/* value*//*, int role ){
        if( !index.isValid()){
            return false;
        }

        if( !(role==Qt::EditRole || role==Qt::CheckStateRole) ){
            return false;
        }

        if(index.row()<0 ||
                index.row()>=mNumberOfProjets ||
                index.column()<0 ||
                index.column()>=mNumberOfDay)
        {
            return false;
        }

        TableModel::Model& dateProj=mFactory.getModel("DateProjets");
        TableModel::Model& proj=mFactory.getModel("Projets");

        bool mustAdd=true;

        for(int i(0); i<dateProj.rowCount();i++){
            QDate date=dateProj.data(dateProj.index(i, 0)).toDate();
            TableModel::ModelForeignKey projet=dateProj.data(dateProj.index(i, 1)).value<TableModel::ModelForeignKey>();

            if( (proj.rowIndexFromId(projet.getId())==index.row()) &&
                    (date.year()==mYear) &&
                    (date.month()==mMonth) &&
                    (date.day()==index.column()+1))
            {
                dateProj.removeRow(i);
                i--;
                mustAdd=false;
            }
        }

        if(mustAdd){
            dateProj.insertRow(0);
            dateProj.setData(dateProj.index(0, 0), QDate(mYear, mMonth, index.column()+1));

            QVariant var=QVariant::fromValue(TableModel::ModelForeignKey(&mFactory, "Projets", proj.id(index.row())));
            dateProj.setData(dateProj.index(0, 1), var);
        }

        emit(dataChanged(index, index));

        return true;
    }

    Qt::ItemFlags ModelCalendrier::flags(const QModelIndex & index) const{
        if (!index.isValid()){
            return Qt::ItemIsEnabled;
        }

        return QAbstractTableModel::flags(index) | Qt::ItemIsUserCheckable;
    }

    bool ModelCalendrier::insertRows(int row, int count, const QModelIndex &/* parent*//*){
        if(row!=0 || count!=-1){
            return false;
        }

        int newNumberOfProjets = mFactory.getModel("Projets").rowCount();

        beginInsertRows(QModelIndex(), 0, newNumberOfProjets-1);
        mNumberOfProjets=newNumberOfProjets;
        endInsertRows();
        return true;
    }

    bool ModelCalendrier::removeRows(int row, int count, const QModelIndex & /*parent*//*){
        if(row!=0 || count!=-1 || mNumberOfProjets==0){
            return false;
        }

        beginRemoveRows(QModelIndex(), 0, mNumberOfProjets-1);
        mNumberOfProjets=0;
        endRemoveRows();
        return true;
    }

    void ModelCalendrier::setYear(int year){
        mYear=year;
        update();
    }

    void ModelCalendrier::setMonth(int month){
        mMonth=month;
        update();
    }

    int ModelCalendrier::getYear(){
        return mYear;
    }

    int ModelCalendrier::getMonth(){
        return mMonth;
    }
    void ModelCalendrier::update(){
        removeColumns(0, -1);
        insertColumns(0, -1);
    }
    bool ModelCalendrier::insertColumns(int col, int count, const QModelIndex & /*parent*//*){
        if(col!=0 || count!=-1 || mNumberOfDay!=0){
            return false;
        }

        QDate currentDate(mYear, mMonth, 1);
        int newNumberOfDay=currentDate.daysInMonth();

        beginInsertColumns(QModelIndex(), 0,  newNumberOfDay-1);

        mNumberOfDay= newNumberOfDay;

        endInsertColumns();
        return true;
    }

    bool ModelCalendrier::removeColumns(int col, int count, const QModelIndex & /*parent*//*){
        if(col!=0 || count!=-1 || mNumberOfDay==0){
            cerr<<"erreur ModelCalendrier::removeColumns"<<endl;
            return false;
        }

        beginRemoveColumns(QModelIndex(), 0, mNumberOfDay-1);
        mNumberOfDay=0;
        endRemoveColumns();
        return true;
    }
    QVariant ModelCalendrier::headerData (int section, Qt::Orientation orientation, int role)const{
        if (role != Qt::DisplayRole){
            return QVariant();
        }

        if (orientation == Qt::Horizontal) {
            if(section>=0 && section<mNumberOfDay){
                return section+1;
            }
        }else if(orientation == Qt::Vertical){
            if(section>=0 && section<mNumberOfProjets){
                TableModel::Model& mdl=mFactory.getModel("Projets");
                if(section<mdl.rowCount()){
                    return mdl.data(mdl.index(section, 0));
                }
            }
        }
        return QVariant();
    }
    void ModelCalendrier::updateProjet(){
        removeRows(0, -1);
        insertRows(0, -1);
    }

    bool ModelCalendrier::stage(int day) const{
        TableModel::Model& stage=mFactory.getModel("PeriodeDeStages");

        for(int i=0;i<stage.rowCount();i++){
            QDate current(mYear, mMonth, day);
            QDate begin=stage.data(stage.index(i, 0)).toDate();
            QDate fin=stage.data(stage.index(i, 1)).toDate();
            if(begin<=current && current<=fin){
                return true;
            }
        }

        return false;
    }

    bool ModelCalendrier::vacances(int day) const{
        TableModel::Model& vacances=mFactory.getModel("VacancesScolaires");

        for(int i=0;i<vacances.rowCount();i++){
            QDate current(mYear, mMonth, day);
            QDate begin=vacances.data(vacances.index(i, 0)).toDate();
            QDate fin=vacances.data(vacances.index(i, 1)).toDate();
            if(begin<=current && current<=fin){
                return true;
            }
        }

        return false;
    }
    bool ModelCalendrier::CCF(int day) const{
        TableModel::Model& CCF=mFactory.getModel("CCF");

        for(int i=0;i<CCF.rowCount();i++){
            QDate current(mYear, mMonth, day);
            QDate begin=CCF.data(CCF.index(i, 1)).toDate();
            QDate fin=CCF.data(CCF.index(i, 2)).toDate();
            if(begin<=current && current<=fin){
                return true;
            }
        }

        return false;
    }
    bool ModelCalendrier::projet(int day, int projetIndex) const{
        TableModel::Model& mdl=mFactory.getModel("DateProjets");
        TableModel::Model& proj=mFactory.getModel("Projets");

        for(int i(0); i<mdl.rowCount(); i++){
            QDate date=mdl.data(mdl.index(i, 0)).toDate();
            TableModel::ModelForeignKey projet=mdl.data(mdl.index(i, 1)).value<TableModel::ModelForeignKey>();

            if(proj.rowIndexFromId(projet.getId())==projetIndex &&
                    date.year()==mYear &&
                    date.month()==mMonth &&
                    date.day()==day){
                return true;
            }
        }

        return false;
    }*/
}
