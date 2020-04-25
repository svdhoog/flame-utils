////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2008 Vehbi Sinan Tunalioglu <vst@vsthost.com>           //
//                                                                        //
//  This file is part of xmme.                                            //
//                                                                        //
//  xmme is free software: you can redistribute it and/or                 //
//  modify it under the terms of the GNU General Public License           //
//  as published by the Free Software Foundation, either version 3        //
//  of the License, or (at your option) any later version.                //
//                                                                        //
//  xmme is distributed in the hope that it will be useful, but           //
//  WITHOUT ANY WARRANTY; without even the implied warranty of            //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     //
//  General Public License for more details.                              //
//                                                                        //
//  You should have received a copy of the GNU General Public License     //
//  along with xmme.  If not, see <http://www.gnu.org/licenses/>.         //
////////////////////////////////////////////////////////////////////////////

#ifndef XMODELTREE_H
#define XMODELTREE_H

#include <qabstractitemmodel.h>
#include <XM.h>
#include <XModel.h>

class XNothing;
class XTreeLabel;
class XAgent;
class XAgentList;
class XModel;
class XModelList;
class XMessage;
class XIOMessage;
class XMessageList;
class XInMessageList;
class XOutMessageList;
class XVariable;
class XVariableList;
class XFunction;
class XFunctionList;
class XFileList;
class XFile;
class XTimeUnitList;
class XTimeUnit;
class XDataType;
class XDataTypeList;

class XModelTree : public QAbstractItemModel {

public:
  XModelTree(XModel *rootItem = 0);
  ~XModelTree();

  ////////////////////////////////////
  // Subclassing QAbstractItemModel //
  ////////////////////////////////////
  //  Qt::ItemFlags flags(const QModelIndex & index) const;
  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
  int rowCount(const QModelIndex & parent = QModelIndex()) const;
  int columnCount(const QModelIndex & parent = QModelIndex()) const;
  bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
  bool setHeaderData(int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole);
  bool setItemData(const QModelIndex & index, const QMap<int, QVariant> & roles);
  bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
  bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
  bool removeRow(int row, const QModelIndex & parent = QModelIndex());
  bool insertColumns(int column, int count, const QModelIndex & parent = QModelIndex());
  bool removeColumns(int column, int count, const QModelIndex & parent = QModelIndex());
  bool removeColumn(int column, const QModelIndex & parent = QModelIndex());
  //bool hasChildren(const QModelIndex & parent = QModelIndex()) const;
  QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
  QModelIndex parent(const QModelIndex & index) const;
  QMimeData * mimeData(const QModelIndexList & indexes) const;
  Qt::DropActions supportedDragActions();
  bool dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent);

  // Checks for the internal pointers
  static bool isTopLevel(QObject *);
  static bool isXModel(QObject *);
  static bool isXModelList(QObject *obj);
  static bool isXEnvironment(QObject *obj);
  static bool isXFile(QObject *obj);
  static bool isXFileList(QObject *obj);
  static bool isXTimeUnit(QObject *obj);
  static bool isXTimeUnitList(QObject *obj);
  static bool isXDataType(QObject *obj);
  static bool isXDataTypeList(QObject *obj);
  static bool isXTreeLabel(QObject *);
  static bool isXAgent(QObject *obj);
  static bool isXAgentList(QObject *obj);
  static bool isXMessage(QObject *obj);
  static bool isXIOMessage(QObject *obj);
  static bool isXMessageList(QObject *obj);
  static bool isXInMessageList(QObject *obj);
  static bool isXOutMessageList(QObject *obj);
  static bool isXVariable(QObject *obj);
  static bool isXVariableList(QObject *obj);
  static bool isXFunction(QObject *obj);
  static bool isXFunctionList(QObject *obj);

  // Convert to QObject's to original classes.
  static XModel * toXModel(QObject *);
  static XModelList * toXModelList(QObject *);
  static XEnvironment * toXEnvironment(QObject *);
  static XFile * toXFile(QObject *);
  static XFileList * toXFileList(QObject *);
  static XTimeUnit * toXTimeUnit(QObject *);
  static XTimeUnitList * toXTimeUnitList(QObject *);
  static XDataType * toXDataType(QObject *);
  static XDataTypeList * toXDataTypeList(QObject *);
  static XAgent * toXAgent(QObject *obj);
  static XAgentList * toXAgentList(QObject *obj);
  static XMessage * toXMessage(QObject *obj);
  static XIOMessage * toXIOMessage(QObject *obj);
  static XMessageList * toXMessageList(QObject *obj);
  static XInMessageList * toXInMessageList(QObject *obj);
  static XOutMessageList * toXOutMessageList(QObject *obj);
  static XVariable * toXVariable(QObject *obj);
  static XVariableList * toXVariableList(QObject *obj);
  static XFunction * toXFunction(QObject *obj);
  static XFunctionList * toXFunctionList(QObject *obj);

  // Custom data retrieval functions
  QVariant dataForXModelWithRole(XModel *model, int role) const;
  QVariant dataForXModelListWithRole(XModelList *modelList, int role) const;
  QVariant dataForXEnvironmentWithRole(XEnvironment *modelList, int role) const;
  QVariant dataForXFileWithRole(XFile *modelList, int role) const;
  QVariant dataForXFileListWithRole(XFileList *modelList, int role) const;
  QVariant dataForXTimeUnitWithRole(XTimeUnit *modelList, int role) const;
  QVariant dataForXTimeUnitListWithRole(XTimeUnitList *modelList, int role) const;
  QVariant dataForXDataTypeWithRole(XDataType *modelList, int role) const;
  QVariant dataForXDataTypeListWithRole(XDataTypeList *modelList, int role) const;
  QVariant dataForXAgentWithRole(XAgent *agent, int role) const;
  QVariant dataForXAgentListWithRole(XAgentList *agentList, int role) const;
  QVariant dataForXMessageWithRole(XMessage *message, int role) const;
  QVariant dataForXIOMessageWithRole(XIOMessage *message, int role) const;
  QVariant dataForXMessageListWithRole(XMessageList *messageList, int role) const;
  QVariant dataForXInMessageListWithRole(XInMessageList *inMessageList, int role) const;
  QVariant dataForXOutMessageListWithRole(XOutMessageList *outMessageList, int role) const;
  QVariant dataForXVariableWithRole(XVariable *variable, int role) const;
  QVariant dataForXVariableListWithRole(XVariableList *variableList, int role) const;
  QVariant dataForXFunctionWithRole(XFunction *function, int role) const;
  QVariant dataForXFunctionListWithRole(XFunctionList *functionList, int role) const;

  // Other convenience functions
  static QString getClassName(QObject *obj);
  static XM::NodeType getXMNodeType(QObject *obj);

private:
  XModel *rootItem;
  XNothing *nothing;
  QList<XTreeLabel*> labels;

  QObject* itemFromIndex(const QModelIndex &index) const;
  XTreeLabel* lookupLabel(QObject*) const;
};

class XTreeLabel : public QObject {

Q_OBJECT

public:

  XTreeLabel(QString label, QObject *parent, int row){
	this->label = label;
	this->parent = parent;
	this->row = row;
  }

  QString label;
  QObject *parent;
  int row;
};

class XNothing : public QObject {

Q_OBJECT

public:

};

#endif
