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

#ifndef XWIDGETEDITMODEL_H
#define XWIDGETEDITMODEL_H

#include <qdebug.h>
#include <QWidget>
#include <ui_XWidgetEditModel.h>
#include <QModelIndex>

#include <XModel.h>

class XWidgetEditModel : public QWidget, Ui::XWidgetEditModel {

Q_OBJECT

public:
  XWidgetEditModel(XModel *model, const QModelIndex &index){
	setupUi(this);
	this->model = model;
	this->index = index;

	this->name->setText(this->model->getName());
	this->version->setText(this->model->getVersion());
	this->description->setText(this->model->getDescription());
	this->filePath->setText(this->model->getFilePath());
	
	connect(this->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(this->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  }

signals:
  void dataChanged(const QModelIndex &index);
  
private slots:

  void accept(){
	this->model->setName(this->name->text());
	this->model->setVersion(this->version->text());
	this->model->setDescription(this->description->toPlainText());
	if(this->filePath->text() == ""){
	  this->filePath->setText(this->model->getFilePath());
	}
	this->model->setFilePath(this->filePath->text());
	emit dataChanged(this->index);
  }

  void reject(){
	this->name->setText(this->model->getName());
	this->version->setText(this->model->getVersion());
	this->description->setText(this->model->getDescription());
	this->filePath->setText(this->model->getFilePath());
  }

private:

  XModel *model;
  QModelIndex index;

};
#endif
