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

#ifndef XWIDGETEDITMESSAGE_H
#define XWIDGETEDITMESSAGE_H

#include <qdebug.h>
#include <QWidget>
#include <ui_XWidgetEditMessage.h>
#include <QModelIndex>

#include <XMessage.h>

class XWidgetEditMessage : public QWidget, Ui::XWidgetEditMessage {

Q_OBJECT

public:
  XWidgetEditMessage(XMessage *message, const QModelIndex &index){
	setupUi(this);
	this->message = message;
	this->index = index;

	this->name->setText(this->message->getName());
	this->description->setText(this->message->getDescription());
	
	connect(this->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(this->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  }

signals:
  void dataChanged(const QModelIndex &index);
  
private slots:

  void accept(){
	this->message->setName(this->name->text());
	this->message->setDescription(this->description->toPlainText());
	emit dataChanged(this->index);
  }

  void reject(){
	this->name->setText(this->message->getName());
	this->description->setText(this->message->getDescription());
  }

private:

  XMessage *message;
  QModelIndex index;

};
#endif
