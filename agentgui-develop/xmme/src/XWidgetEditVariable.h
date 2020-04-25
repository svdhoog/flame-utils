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

#ifndef XWIDGETEDITVARIABLE_H
#define XWIDGETEDITVARIABLE_H

#include <qdebug.h>
#include <QWidget>
#include <ui_XWidgetEditVariable.h>
#include <QModelIndex>

#include <XVariable.h>

class XWidgetEditVariable : public QWidget, Ui::XWidgetEditVariable {

Q_OBJECT

public:
  XWidgetEditVariable(XVariable *variable, const QModelIndex &index){
	setupUi(this);
	this->variable = variable;
	this->index = index;

	this->type->setText(this->variable->getType());
	this->name->setText(this->variable->getName());
	this->description->setText(this->variable->getDescription());
	
	connect(this->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(this->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  }

signals:
  void dataChanged(const QModelIndex &index);
  
private slots:

  void accept(){
	this->variable->setType(this->type->text());
	this->variable->setName(this->name->text());
	this->variable->setDescription(this->description->toPlainText());
	emit dataChanged(this->index);
  }

  void reject(){
	this->type->setText(this->variable->getType());
	this->name->setText(this->variable->getName());
	this->description->setText(this->variable->getDescription());
  }

private:

  XVariable *variable;
  QModelIndex index;

};
#endif
