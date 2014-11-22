/****************************************************************************
 **
 ** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** You may use this file under the terms of the BSD license as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
 **     of its contributors may be used to endorse or promote products derived
 **     from this software without specific prior written permission.
 **
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

 /*
     treemodel.cpp

     Provides a simple tree model to show how to create and use hierarchical
     models.
 */

 #include <QtGui>

#include "tree.h"
#include "item.h"
#include "project.h"

#include <iostream>
using namespace std;

namespace Model
{
    namespace ProjectTree
    {
         Tree::Tree(TableModel::Model& projets, QObject *parent)
             : QAbstractItemModel(parent),
               mProjets(projets)
         {
             connect(&mProjets, &TableModel::Model::rowsInserted,
                     this, &Tree::whenRowInserted);
         }

         Tree::~Tree()
         {

         }

         int Tree::columnCount(const QModelIndex &/*parent*/) const
         {
             return 1;
         }

         QVariant Tree::data(const QModelIndex &index, int role) const
         {
             if (!index.isValid())
                 return QVariant();


             if (role != Qt::DisplayRole && role != Qt::EditRole)
                 return QVariant();

             Item *item = static_cast<Item*>(index.internalPointer());

             return item->name();
         }

         Qt::ItemFlags Tree::flags(const QModelIndex &index) const
         {
             if (!index.isValid())
                 return 0;

             return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
         }

         QVariant Tree::headerData(int section, Qt::Orientation orientation,
                                        int role) const
         {
             if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section == 0)
                 return QVariant("Projets");

             return QVariant();
         }

         QModelIndex Tree::index(int row, int column, const QModelIndex &parent)
                     const
         {
             if (!hasIndex(row, column, parent))
                 return QModelIndex();

             const Item *parentItem;

             if (!parent.isValid())
                 parentItem = &rootItem;
             else
                 parentItem = static_cast<Item*>(parent.internalPointer());

             const Item *childItem = parentItem->child(row);
             if (childItem)
                 return createIndex(row, column, (void*)childItem);
             else
                 return QModelIndex();
         }

         QModelIndex Tree::parent(const QModelIndex &index) const
         {
             if (!index.isValid())
                 return QModelIndex();

             Item *childItem = static_cast<Item*>(index.internalPointer());
             Item *parentItem = childItem->parent();

             if (parentItem == &rootItem)
                 return QModelIndex();

             return createIndex(parentItem->row(), 0, parentItem);
         }

         int Tree::rowCount(const QModelIndex &parent) const
         {
             const Item *parentItem;
             if (parent.column() > 0)
                 return 0;

             if (!parent.isValid())
                 parentItem = &rootItem;
             else
                 parentItem = static_cast<Item*>(parent.internalPointer());

             return parentItem->childCount();
         }

         bool Tree::setData(const QModelIndex & index, const QVariant & value, int role){
             if (!index.isValid())
                 return false;

             if (role != Qt::EditRole)
                 return false;

             Item* item=static_cast<Item*>(index.internalPointer());

             Project *proj = dynamic_cast<Project*>(item);

             if(proj!=NULL){
                 if(index.column()!=0){
                     return false;
                 }

                 if(!mProjets.setData(mProjets.index(mProjets.rowIndexFromId(proj->id()), 0), value)){
                     return false;
                 }

                 emit QAbstractItemModel::dataChanged(index, index, {role});

                 return true;
             }

             return false;
         }

         void Tree::whenRowInserted(const QModelIndex & parent, int start, int end){
             beginInsertRows(QModelIndex(), start, end);
             for(int i(start); i<=end;i++){
                 rootItem.addProject(&mProjets, mProjets.id(i), i);
             }
             endInsertRows();
         }
    }
}
