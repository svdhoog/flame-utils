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

#ifndef XWIDGETEDITIOMESSAGE_H
#define XWIDGETEDITIOMESSAGE_H

#include <qdebug.h>
#include <QWidget>
#include <ui_XWidgetEditIOMessage.h>
#include <QModelIndex>

#include <XIOMessage.h>

class XWidgetEditIOMessage : public QWidget, Ui::XWidgetEditIOMessage {

Q_OBJECT

public:
  XWidgetEditIOMessage(XIOMessage *message, const QModelIndex &index){
	setupUi(this);
	this->message = message;
	this->index = index;

	this->filter->setText(this->message->filter);
	
	connect(this->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(this->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  }

signals:
  void dataChanged(const QModelIndex &index);
  
private slots:

  void accept(){
	this->message->filter = this->filter->toPlainText();
	emit dataChanged(this->index);
  }

  void reject(){
	this->filter->setText(this->message->filter);
  }

private:

  XIOMessage *message;
  QModelIndex index;

};
#endif
