#include "model.h"

#include <iostream>
using namespace std;

#include <QJsonArray>
#include <QString>

namespace Model
{
    namespace TableModel
    {
        QString defaultRowNameFunction(Model& model, int id){
            ModelRow* row=model.rowFromId(id);
            if(row!=NULL){
                return QString("\"")+row->get(0).toString()+"\"";
            }else{
                return "";
            }
        }

        Model::Model(ModelMetadata metadata):
            QAbstractTableModel(NULL),
            mIdMax(0),
            mMetadata(metadata),
            mGetRowName(defaultRowNameFunction)
        {
            mGetRowName=defaultRowNameFunction;
        }

        Model::~Model(){
            for(int i(0);i<mTable.size();i++){
                delete mTable[i];
            }
        }

        int Model::rowCount(const QModelIndex &) const{
            return mTable.size();
        }
        int Model::columnCount(const QModelIndex &) const{
            return mMetadata.size();
        }
        QVariant Model::data(const QModelIndex & index, int role) const{
            if (!index.isValid()){
                return QVariant();
            }

            if (index.row() >= mTable.size() || index.row() < 0){
                return QVariant();
            }

            if (role == Qt::DisplayRole || role == Qt::EditRole) {
                return mTable[index.row()]->get(index.column());
            }
            return QVariant();
        }
        bool Model::setData(const QModelIndex & index, const QVariant & value, int role){

            if( !index.isValid() || role != Qt::EditRole){
                return false;
            }

            if (index.row() >= mTable.size() || index.row() < 0){
                return false;
            }

            if(mTable[index.row()]->set(index.column(), value)){
                emit(dataChanged(index, index));
                return true;
            }else{
                return false;
            }
        }

        Qt::ItemFlags Model::flags(const QModelIndex & index) const{
            if (!index.isValid()){
                return Qt::ItemIsEnabled;
            }

            return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
        }

        bool Model::insertRows(int position, int rows, const QModelIndex & parent ){
            Q_UNUSED(parent);

            if(rows==0){
                return true;
            }

            beginInsertRows(QModelIndex(), position, position+rows-1);

            for (int rowNumber = 0; rowNumber < rows; rowNumber++) {
                QVector<int>::iterator it1=mIds.begin();
                it1+=position;
                mIds.insert(it1, ++mIdMax);

                QVector<ModelRow*>::iterator it2=mTable.begin();
                it2+=position;
                mTable.insert(it2, new ModelRow(mMetadata));
            }

            endInsertRows();

            return true;
        }

        bool Model::removeRows(int position, int rows, const QModelIndex & parent){
            Q_UNUSED(parent);

            if(rows==0){
                return true;
            }

            for (int row = 0; row < rows; ++row) {
                if(mTable[position+row]->isReferenced()){
                    return false;
                }
            }

            beginRemoveRows(QModelIndex(), position, position+rows-1);

            for (int row = 0; row < rows; ++row) {
                delete mTable[position];
                mTable.removeAt(position);
                mIds.removeAt(position);
            }

            endRemoveRows();
            return true;
        }
        QVariant Model::headerData(int section, Qt::Orientation orientation, int role)const{
            if (role != Qt::DisplayRole){
                return QVariant();
            }

            if (orientation == Qt::Horizontal) {
                if(section>=0 && section<mMetadata.size()){
                    return mMetadata.get(section).getName();
                }
            }
            return QVariant();
        }
        int Model::id(int row){
            if(row<0 || row>=rowCount()){
                return -1;
            }
            return mIds[row];
        }
        int Model::rowIndexFromId(int i){
            for(int index(0);index<mIds.size();index++){
                if(mIds[index]==i){
                    return index;
                }
            }
            return -1;
        }
        ModelRow* Model::rowFromId(int id){
            if(id==0){
                return NULL;
            }
            int row=rowIndexFromId(id);
            if(row==-1){
                return NULL;
            }
            return mTable[row];
        }
        ModelRow* Model::rowFromIndex(int index){
            if(index<0 || index>=mTable.size()){
                return NULL;
            }
            return mTable[index];
        }
        QString Model::getRowName(int id){
            if(mGetRowName){
                return mGetRowName(*this, id);
            }else{
                return "erreur";
            }
        }

        void Model::setRowNameFonction(std::function<QString(Model&, int)> func){
            mGetRowName=func;
        }
        ModelMetadata& Model::getMetadata(){
            return mMetadata;
        }
        bool Model::readJsonValue(QJsonValue value){
            if(!value.isArray()){
                return false;
            }

            QJsonArray rows=value.toArray();

            for(int rowNum(0); rowNum<rows.size();rowNum++){
                //cout<<"\trow "<<rowNum+1<<" / "<<rows.size()<<endl;

                QJsonValue rowValue=rows[rowNum];

                if(!mTable.at(rowNum)->readJsonValue(rowValue)){
                    return false;
                }
            }

            return true;
        }
    }
}
