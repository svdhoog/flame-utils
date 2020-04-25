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

#ifndef XWIDGETEDITFILE_H
#define XWIDGETEDITFILE_H

#include <qdebug.h>
#include <QWidget>
#include <ui_XWidgetEditFile.h>
#include <QModelIndex>

#include <XFile.h>
#include <qfiledialog.h>

class XWidgetEditFile : public QWidget, Ui::XWidgetEditFile {

Q_OBJECT

public:
  XWidgetEditFile(XFile *file, const QModelIndex &index){
	setupUi(this);
	this->file = file;
	this->index = index;

	this->filePath->setText(this->file->getFilePath());
	
	connect(this->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(this->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(this->selectButton, SIGNAL(pressed()), this, SLOT(getFilePath()));
  }

signals:
  void dataChanged(const QModelIndex &index);
  
private slots:

  void accept(){
	this->file->setFilePath(this->filePath->text());
	emit dataChanged(this->index);
  }

  void reject(){
	this->filePath->setText(this->file->getFilePath());
  }

  void getFilePath(){
	this->filePath->setText(QFileDialog::getOpenFileName(0,
														 "Select File",
														 ".",
														 "C Files (*.c);;All Files (*.*)"));
  }

private:

  XFile *file;
  QModelIndex index;

};
#endif
