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

#ifndef XWIDGETEDITAGENT_H
#define XWIDGETEDITAGENT_H

#include <qdebug.h>
#include <QWidget>
#include <ui_XWidgetEditAgent.h>
#include <QModelIndex>

#include <XAgent.h>

class XWidgetEditAgent : public QWidget, Ui::XWidgetEditAgent {

Q_OBJECT

public:
  XWidgetEditAgent(XAgent *agent, const QModelIndex &index){
	setupUi(this);
	this->agent = agent;
	this->index = index;

	this->name->setText(this->agent->getName());
	this->description->setText(this->agent->getDescription());
	
	connect(this->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(this->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  }

signals:
  void dataChanged(const QModelIndex &index);
  
private slots:

  void accept(){
	this->agent->setName(this->name->text());
	this->agent->setDescription(this->description->toPlainText());
	emit dataChanged(this->index);
  }

  void reject(){
	this->name->setText(this->agent->getName());
	this->description->setText(this->agent->getDescription());
  }

private:

  XAgent *agent;
  QModelIndex index;

};
#endif
