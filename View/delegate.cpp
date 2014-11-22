#include "delegate.h"

#include "Model/TableModel/modelforeignkey.h"

#include "foreignkeyeditor.h"

#include "Model/factory.h"

#include <QPainter>

namespace View
{
    Delegate::Delegate(QObject *parent) :
        QStyledItemDelegate(parent)
    {
    }

    void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
    {
        if (index.data().canConvert<Model::TableModel::ModelForeignKey>()) {
            Model::TableModel::ModelForeignKey foreignKey =
                    qvariant_cast<Model::TableModel::ModelForeignKey>(index.data());

            if (option.state & QStyle::State_Selected) {
                painter->fillRect(option.rect, option.palette.highlight());
            }
            Model::TableModel::Model* model=foreignKey.getModel();
            QString item;
            if(foreignKey.getId()!=0){
                item=model->getRowName(foreignKey.getId());
            }

            painter->drawText(option.rect, Qt::AlignCenter, item);
         } else {
             QStyledItemDelegate::paint(painter, option, index);
         }
    }

    QSize Delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        return QStyledItemDelegate::sizeHint(option, index);
    }

    QWidget* Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
    {
        if (index.data().canConvert<Model::TableModel::ModelForeignKey>()) {
             ForeignKeyEditor *editor = new ForeignKeyEditor(parent);
             return editor;
         } else {
             return QStyledItemDelegate::createEditor(parent, option, index);
         }
    }

    void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        if (index.data().canConvert<Model::TableModel::ModelForeignKey>()) {
             Model::TableModel::ModelForeignKey foreignKey = qvariant_cast<Model::TableModel::ModelForeignKey>(index.data());
             ForeignKeyEditor *foreignKeyEditor = qobject_cast<ForeignKeyEditor *>(editor);
             foreignKeyEditor->setForeignKey(foreignKey);
         } else {
             QStyledItemDelegate::setEditorData(editor, index);
         }
    }

    void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
    {
        if (index.data().canConvert<Model::TableModel::ModelForeignKey>()) {
             ForeignKeyEditor *foreignKeyEditor = qobject_cast<ForeignKeyEditor *>(editor);
             model->setData(index, QVariant::fromValue(foreignKeyEditor->getForeignKey()));
         } else {
             QStyledItemDelegate::setModelData(editor, model, index);
         }
    }
}
