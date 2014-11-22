#include "modelmetadata.h"

namespace Model
{
    namespace TableModel
    {
        ModelMetadataColumn& ModelMetadataColumn::setName(QString name){
            mName=name;
            return *this;
        }

        ModelMetadataColumn& ModelMetadataColumn::setType(Type type){
            mType=type;
            return *this;
        }

        ModelMetadataColumn& ModelMetadataColumn::setForeignKey(Model* foreignKey){
            mForeignKey=foreignKey;
            return *this;
        }
        QString ModelMetadataColumn::getName() const{
            return mName;
        }
        Type ModelMetadataColumn::getType() const{
            return mType;
        }
        Model* ModelMetadataColumn::getForeignKey() const{
            return mForeignKey;
        }


        ModelMetadataColumn& ModelMetadata::add(){
            mColumns.push_back(ModelMetadataColumn());
            return mColumns[mColumns.size()-1];
        }

        int ModelMetadata::size() const{
            return mColumns.size();
        }

        ModelMetadataColumn& ModelMetadata::get(int index){
            return mColumns[index];
        }

        const ModelMetadataColumn& ModelMetadata::get(int index) const{
            return mColumns[index];
        }

        void ModelMetadata::clear(){
            mColumns.clear();
        }
    }
}
