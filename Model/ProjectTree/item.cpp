#include "item.h"

namespace Model
{
    namespace ProjectTree
    {
        Item::Item(Item* parent):
            QObject(parent)
        {
        }

        Item* Item::parent(){
            return static_cast<Item*>(QObject::parent());
        }

        const Item* Item::parent()const{
            return static_cast<const Item*>(QObject::parent());
        }


        Item *Item::child(int row){
            return mChilds[row];
        }

        const Item *Item::child(int row)const{
            return mChilds[row];
        }

        int Item::childCount() const{
            return mChilds.size();
        }

        int Item::row() const
        {
            if (parent()){
                return parent()->mChilds.indexOf(const_cast<Item*>(this));
            }

            return 0;
        }

        void Item::addChild(Item* child, int pos){
            mChilds.insert(mChilds.begin()+pos, child);
        }
    }
}
