#ifndef MODELPROJECTSTREEITEM_H
#define MODELPROJECTSTREEITEM_H

#include <QObject>

namespace Model
{
    namespace ProjectTree
    {
        class Item : public QObject
        {
            Q_OBJECT
        public:
            Item(Item* parent=0);

            virtual QString name()=0;

            Item *child(int row);
            const Item *child(int row)const;
            int childCount() const;

            int row() const;

            Item* parent();
            const Item* parent() const;

        protected:
            void addChild(Item* child, int pos);

        private:
            QList<Item*> mChilds;

        };
    }
}

#endif // MODELPROJECTSTREEITEM_H
