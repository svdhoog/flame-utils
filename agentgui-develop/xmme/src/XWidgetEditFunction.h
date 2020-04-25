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

#ifndef XWIDGETEDITFUNCTION_H
#define XWIDGETEDITFUNCTION_H

#include <qdebug.h>
#include <QWidget>
#include <ui_XWidgetEditFunction.h>
#include <QModelIndex>

#include <XFunction.h>
#include <qscilexertex.h>

class XWidgetEditFunction : public QWidget, Ui::XWidgetEditFunction {

Q_OBJECT

public:
  XWidgetEditFunction(XFunction *function, const QModelIndex &index){
	setupUi(this);
	QsciLexerTeX *sciLexer = new QsciLexerTeX;
	sciLexer->setFont(QFont("monospace"));

	this->description->setLexer(sciLexer);

	this->function = function;
	this->index = index;

	this->name->setText(this->function->getName());
	this->currentState->setText(this->function->getCurrentState());
	this->nextState->setText(this->function->getNextState());
	this->code->setText(this->function->getCode());
	this->description->setText(this->function->getDescription());	
	this->condition->setText(this->function->getCondition());	

	connect(this->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(this->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  }

signals:
  void dataChanged(const QModelIndex &index);
  
private slots:

  void accept(){
	this->function->setName(this->name->text());
	this->function->setCurrentState(this->currentState->text());
	this->function->setNextState(this->nextState->text());
	this->function->setDescription(this->description->text());
	this->function->setCode(this->code->toPlainText());
	this->function->setCondition(this->condition->toPlainText());
	emit dataChanged(this->index);
  }

  void reject(){
	this->name->setText(this->function->getName());
	this->currentState->setText(this->function->getCurrentState());
	this->nextState->setText(this->function->getNextState());
	this->code->setText(this->function->getCode());
	this->description->setText(this->function->getDescription());
	this->condition->setText(this->function->getCondition());	
  }

private:

  XFunction *function;
  QModelIndex index;

};
#endif
