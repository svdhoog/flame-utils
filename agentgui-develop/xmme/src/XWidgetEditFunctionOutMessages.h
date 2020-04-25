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

#ifndef XWIDGETEDITFUNCTIONOUTMESSAGES_H
#define XWIDGETEDITFUNCTIONOUTMESSAGES_H

#include <qdebug.h>
#include <QWidget>
#include <ui_XWidgetEditFunctionOutMessages.h>
#include <QModelIndex>

#include <XFunction.h>
#include <XMessage.h>
#include <XAgent.h>
#include <XOutMessageList.h>
#include <XFunctionList.h>
#include <XAgentList.h>
#include <XModel.h>
#include <qabstractitemview.h>
#include <XIOMessage.h>


class XWidgetEditFunctionOutMessages : public QWidget, Ui::XWidgetEditFunctionOutMessages {

Q_OBJECT

public:
  XWidgetEditFunctionOutMessages(XOutMessageList *outList, const QModelIndex &index){
	setupUi(this);
	this->outList = outList;
	this->allMessages = this->outList->getTopLevelModel()->getAllMessages();
	this->index = index;
	this->messagesList->setSelectionMode(QAbstractItemView::MultiSelection);

	for(int i = 0; i < this->allMessages.size(); i++){
	  QListWidgetItem *tmp = new QListWidgetItem(this->allMessages.at(i)->getName());
	  tmp->setData(Qt::DisplayRole, this->allMessages.at(i)->getName());

	  this->messagesList->addItem(tmp);

	  for(int j = 0; j < this->outList->messageList.count(); j++){
		if(this->outList->messageList.at(j)->msgPointer == this->allMessages.at(i)){
		  tmp->setSelected(true);
		}
	  }

	}

	connect(this->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(this->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  }

signals:
  void dataChanged(const QModelIndex &index);
  void dataChanged(const QModelIndex &index, const QModelIndex &index2);
  
private slots:

  void accept(){
	QList<XIOMessage*> newMessageList;
 	for(int i = 0; i < this->messagesList->count(); i++){
	  if(this->messagesList->item(i)->isSelected()){
		newMessageList.append(new XIOMessage(this->allMessages.at(i), this->outList));
	  }
	}
	this->outList->messageList = newMessageList;
	emit dataChanged(this->index, this->index);
  }

  void reject(){
  }

private:

  XOutMessageList *outList;
  QModelIndex index;
  QList<XMessage*> allMessages;

};
#endif
