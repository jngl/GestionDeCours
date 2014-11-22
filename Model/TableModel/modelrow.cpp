#include "modelrow.h"

#include "modelforeignkey.h"
#include "model.h"

#include <assert.h>

#include <QDate>
#include <QJsonObject>

#include <iostream>
using namespace std;

namespace Model
{
    namespace TableModel
    {
        ModelRow::ModelRow(ModelMetadata& metadata):
            mMetadata(metadata),
            mData(mMetadata.size()),
            mReferenceNumber(0)
        {
            for(int i(0);i<mMetadata.size();i++){
                switch(mMetadata.get(i).getType()){
                case Type_INT:
                    mData[i]=0;
                    break;
                case Type_STRING:
                    mData[i]="";
                    break;
                case Type_FOREYGN_KEY:
                    mData[i].setValue(ModelForeignKey(mMetadata.get(i).getForeignKey()));
                    break;
                case Type_DATE:
                    mData[i]=QDate::currentDate();
                    break;
                }
            }
        }

        bool ModelRow::set(int index, QVariant value){
            if(index<0 || index>mMetadata.size()){
                return false;
            }

            int i=0;
            QString str;
            bool ok=true;

            switch(mMetadata.get(index).getType()){
            case Type_INT:
                i=value.toInt(&ok);
                if(!ok){
                    return false;
                }
                mData[index]=i;
                break;
            case Type_STRING:
                if(value.type()!=QVariant::String){
                    return false;
                }
                mData[index]=value.toString();
                break;
            case Type_FOREYGN_KEY:
                if(!value.canConvert<ModelForeignKey>()){
                    return false;
                }
                mData[index]=value;
                break;
            case Type_DATE:
                if(value.type()!=QVariant::Date){
                    return false;
                }
                mData[index]=value;
            }

            return true;
        }

        QVariant ModelRow::get(int index){
            if(index<0 || index>mMetadata.size()){
                return QVariant();
            }else{
                return mData[index];
            }
        }
        bool ModelRow::isReferenced(){
            return mReferenceNumber!=0;
        }

        void ModelRow::addReference(){
            mReferenceNumber++;
        }

        void ModelRow::deleteRefence(){
            mReferenceNumber--;
            assert(mReferenceNumber>=0);
        }
        bool ModelRow::readJsonValue(QJsonValue value){
            if(!value.isObject()){
                return false;
            }

            QJsonObject rowObject=value.toObject();

            for(int colNum(0); colNum<mMetadata.size();colNum++){
                QJsonValue item=rowObject[mMetadata.get(colNum).getName()];

                bool ok;

                switch(mMetadata.get(colNum).getType()){
                case Type_DATE:
                    ok=readDateJsonValue(colNum, item);
                    break;
                case Type_FOREYGN_KEY:
                    ok=readForeignKeyValue(colNum, item);
                    break;
                case Type_INT:
                    ok=readIntJsonValue(colNum, item);
                    break;
                case Type_STRING:
                    ok=readStringJsonValue(colNum, item);
                    break;
                }

                if(!ok){
                    return false;
                }
            }

            return true;
        }
        bool ModelRow::readDateJsonValue(int index, QJsonValue value){
            //cout<<"\t\tread date"<<endl;
            if(value.isNull()){
                return true;
            }

            if(!value.isDouble()){
                return false;
            }

            QDate date;
            date=QDate::fromJulianDay(value.toInt());

            set(index, QVariant(date));

            return true;
        }

        bool ModelRow::readForeignKeyValue(int index, QJsonValue value){
            //cout<<"\t\tread Foreign Key"<<endl;
            if(value.isNull()){
                return true;
            }

            if(!value.isDouble()){
                return false;
            }

            if(value.toInt()==-1){
                return true;
            }

            Model* model=mMetadata.get(index).getForeignKey();

            ModelForeignKey foreignKey(mMetadata.get(index).getForeignKey(), model->id(value.toInt()));

            QVariant var;
            var.setValue(foreignKey);

            set(index, var);

            return true;
        }

        bool ModelRow::readIntJsonValue(int index, QJsonValue value){
            //cout<<"\t\tread int"<<endl;
            if(value.isNull()){
                return true;
            }

            if(!value.isDouble() && !value.isString()){
                return false;
            }

            set(index, QVariant(value.toInt()));

            return true;
        }

        bool ModelRow::readStringJsonValue(int index, QJsonValue value){
            //cout<<"\t\tread string"<<endl;
            if(value.isNull()){
                return true;
            }

            if(!value.isString()){
                return false;
            }

            set(index, QVariant(value.toString()));

            return true;
        }
    }
}
