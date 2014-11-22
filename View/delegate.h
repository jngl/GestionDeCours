#ifndef VIEWDELEGATE_H
#define VIEWDELEGATE_H

#include <QStyledItemDelegate>

namespace View
{
    class Delegate : public QStyledItemDelegate
    {
        Q_OBJECT
    public:
        explicit Delegate(QObject *parent = 0);

        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    signals:

    public slots:

    };
};

#endif // VIEWDELEGATE_H
