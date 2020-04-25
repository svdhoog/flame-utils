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

#ifndef XMODELVIEW_H
#define XMODELVIEW_H

#include <QObject>
#include <qtreeview.h>

class XModelView : public QTreeView {

Q_OBJECT

public:
  XModelView(QWidget * parent = 0);
  ~XModelView();
  void setModel(QAbstractItemModel * model);
  void setParentWindow(QWidget *);

private:
  QWidget* parentWidget;
  void showEditWidget(const QModelIndex &index);
  QAction* actionAddModel;
  QAction* actionDeleteModel;
  QAction* actionEnableModel;
  QAction* actionDisableModel;
  QAction* actionAddAgent;
  QAction* actionDeleteAgent;
  QAction* actionAddMessage;
  QAction* actionDeleteMessage;
  QAction* actionAddConstant;
  QAction* actionDeleteConstant;
  QAction* actionAddFunctionFile;
  QAction* actionDeleteFunctionFile;
  QAction* actionAddTimeUnit;
  QAction* actionDeleteTimeUnit;
  QAction* actionAddDataType;
  QAction* actionDeleteDataType;
  QAction* actionAddVariable;
  QAction* actionDeleteVariable;
  QAction* actionAddFunction;
  QAction* actionDeleteFunction;
  QAction* actionAddInputMessage;
  QAction* actionDeleteIOMessage;
  QAction* actionAddOutputMessage;

protected:
  void contextMenuEvent(QContextMenuEvent * ev);
											   
public slots:
  void displayXMML(const QModelIndex &index);
  void itemActivated(const QModelIndex & index1, const QModelIndex & index2);
  // All the context menu actions declared here:
  void addModel();
  void deleteModel();
  void enableModel();
  void disableModel();
  void addAgent();
  void deleteAgent();
  void addMessage();
  void deleteMessage();
  void addConstant();
  void deleteConstant();
  void addFunctionFile();
  void deleteFunctionFile();
  void addTimeUnit();
  void deleteTimeUnit();
  void addDataType();
  void deleteDataType();
  void addVariable();
  void deleteVariable();
  void addFunction();
  void deleteFunction();
  void addInputMessage();
  void deleteInputMessage();
  void addOutputMessage();
  void deleteOutputMessage();
};

#endif
