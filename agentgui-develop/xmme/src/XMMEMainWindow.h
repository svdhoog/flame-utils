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

#ifndef XMMEMAINWINDOW_H
#define XMMEMAINWINDOW_H

#include <QMainWindow>
#include <ui_XMMEMainWindow.h>

class XModel;
class XModelTree;
class QModelIndex;
class XAgent;
class XVariable;
class XFunction;
class XMessage;
class XIOMessage;
class XInMessageList;
class XOutMessageList;
class XTimeUnit;
class XFile;
class XDataType;
class QCloseEvent;

class XMMEMainWindow : public QMainWindow, Ui::XMMEMainWindow {

Q_OBJECT

public:
  XMMEMainWindow(QString filePath);
  void showInfo(QString info);
  void editModel(XModel *model, const QModelIndex &index);
  void editAgent(XAgent *agent, const QModelIndex &index);
  void editVariable(XVariable *variable, const QModelIndex &index);
  void editFunction(XFunction *function, const QModelIndex &index);
  void editMessage(XMessage *message, const QModelIndex &index);
  void editIOMessage(XIOMessage *IOmessage, const QModelIndex &index);
  void editTimeUnit(XTimeUnit *timeUnit, const QModelIndex &index);
  void editFile(XFile *file, const QModelIndex &index);
  void editDataType(XDataType *dataType, const QModelIndex &index);
  void editInputMessages(XInMessageList *inList, const QModelIndex &index);
  void editOutputMessages(XOutMessageList *outList, const QModelIndex &index);
  void editNull();
  void emptyEditingLayout();
  void closeEvent(QCloseEvent*);

private slots:
  void dataChanged(const QModelIndex&);
  void actionSlotNew();
  void actionSlotOpen();
  void actionSlotSave();
  void actionSlotQuit();
  void actionSlotAbout();

private:

  XModel * model;
  XModelTree * viewModel;

};
#endif
