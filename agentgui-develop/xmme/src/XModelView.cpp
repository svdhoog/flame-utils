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

#include <qdebug.h>
#include <qdatetime.h>

#include "XModelTree.h"
#include "XModelView.h"
#include "XMMEMainWindow.h"

#include <XAgent.h>
#include <XAgentList.h>
#include <XDataType.h>
#include <XDataTypeList.h>
#include <XEnvironment.h>
#include <XFile.h>
#include <XFileList.h>
#include <XFunction.h>
#include <XFunctionList.h>
#include <XIOMessage.h>
#include <XInMessageList.h>
#include <XM.h>
#include <XMessage.h>
#include <XMessageList.h>
#include <XModel.h>
#include <XModelList.h>
#include <XOutMessageList.h>
#include <XTimeUnit.h>
#include <XTimeUnitList.h>
#include <XVariable.h>
#include <XVariableList.h>
#include <qevent.h>

XModelView::XModelView(QWidget *){
  // Initialize the actions for the context menu
  this->actionAddModel
	= new QAction(QIcon(":/icons/xmme/images/addModel.png"), tr("AddModel"), this);
  this->actionDeleteModel
	= new QAction(QIcon(":/icons/xmme/images/deleteModel.png"), tr("Delete Model"), this);
  this->actionEnableModel
	= new QAction(QIcon(":/icons/xmme/images/enableModel.png"), tr("Enable Model"), this);
  this->actionDisableModel
	= new QAction(QIcon(":/icons/xmme/images/disableModel.png"), tr("Disable Model"), this);
  this->actionAddAgent
	= new QAction(QIcon(":/icons/xmme/images/addAgent.png"), tr("Add Agent"), this);
  this->actionDeleteAgent
	= new QAction(QIcon(":/icons/xmme/images/deleteAgent.png"), tr("Delete Agent"), this);
  this->actionAddMessage
	= new QAction(QIcon(":/icons/xmme/images/addMessage.png"), tr("Add Message"), this);
  this->actionDeleteMessage
	= new QAction(QIcon(":/icons/xmme/images/deleteMessage.png"), tr("Delete Message"), this);
  this->actionAddConstant
	= new QAction(QIcon(":/icons/xmme/images/addConstant.png"), tr("Add Constant"), this);
  this->actionDeleteConstant
	= new QAction(QIcon(":/icons/xmme/images/deleteConstant.png"), tr("Delete Constant"), this);
  this->actionAddFunctionFile
	= new QAction(QIcon(":/icons/xmme/images/addFunctionFile.png"), tr("Add Function File"), this);
  this->actionDeleteFunctionFile
	= new QAction(QIcon(":/icons/xmme/images/deleteFunctionFile.png"), tr("Delete Function File"), this);
  this->actionAddTimeUnit
	= new QAction(QIcon(":/icons/xmme/images/addTimeUnit.png"), tr("Add Time Unit"), this);
  this->actionDeleteTimeUnit
	= new QAction(QIcon(":/icons/xmme/images/deleteTimeUnit.png"), tr("Delete Time Unit"), this);
  this->actionAddDataType
	= new QAction(QIcon(":/icons/xmme/images/addDataType.png"), tr("Add Data Type"), this);
  this->actionDeleteDataType
	= new QAction(QIcon(":/icons/xmme/images/deleteDataType.png"), tr("Delete Data Type"), this);
  this->actionAddVariable
	= new QAction(QIcon(":/icons/xmme/images/addVariable.png"), tr("Add Variable"), this);
  this->actionDeleteVariable
	= new QAction(QIcon(":/icons/xmme/images/deleteVariable.png"), tr("Delete Variable"), this);
  this->actionAddFunction
	= new QAction(QIcon(":/icons/xmme/images/addFunction.png"), tr("Add Function"), this);
  this->actionDeleteFunction
	= new QAction(QIcon(":/icons/xmme/images/deleteFunction.png"), tr("Delete Function"), this);
  this->actionAddInputMessage
	= new QAction(QIcon(":/icons/xmme/images/addInputMessage.png"), tr("Add Input Message"), this);
  this->actionDeleteIOMessage
	= new QAction(QIcon(":/icons/xmme/images/deleteIOMessage.png"), tr("Delete Input/Output Message"), this);
  this->actionAddOutputMessage
	= new QAction(QIcon(":/icons/xmme/images/addOutputMessage.png"), tr("Add Output Message"), this);

  // Connect the actions to the matched operations.
  connect(actionAddModel, SIGNAL(triggered()), this, SLOT(addModel()));
  connect(actionDeleteModel, SIGNAL(triggered()), this, SLOT(deleteModel()));
  connect(actionEnableModel, SIGNAL(triggered()), this, SLOT(enableModel()));
  connect(actionDisableModel, SIGNAL(triggered()), this, SLOT(disableModel()));
  connect(actionAddAgent, SIGNAL(triggered()), this, SLOT(addAgent()));
  connect(actionDeleteAgent, SIGNAL(triggered()), this, SLOT(deleteAgent()));
  connect(actionAddMessage, SIGNAL(triggered()), this, SLOT(addMessage()));
  connect(actionDeleteMessage, SIGNAL(triggered()), this, SLOT(deleteMessage()));
  connect(actionAddConstant, SIGNAL(triggered()), this, SLOT(addConstant()));
  connect(actionDeleteConstant, SIGNAL(triggered()), this, SLOT(deleteVariable()));
  connect(actionAddFunctionFile, SIGNAL(triggered()), this, SLOT(addFunctionFile()));
  connect(actionDeleteFunctionFile, SIGNAL(triggered()), this, SLOT(deleteFunctionFile()));
  connect(actionAddTimeUnit, SIGNAL(triggered()), this, SLOT(addTimeUnit()));
  connect(actionDeleteTimeUnit, SIGNAL(triggered()), this, SLOT(deleteTimeUnit()));
  connect(actionAddDataType, SIGNAL(triggered()), this, SLOT(addDataType()));
  connect(actionDeleteDataType, SIGNAL(triggered()), this, SLOT(deleteDataType()));
  connect(actionAddVariable, SIGNAL(triggered()), this, SLOT(addVariable()));
  connect(actionDeleteVariable, SIGNAL(triggered()), this, SLOT(deleteVariable()));
  connect(actionAddFunction, SIGNAL(triggered()), this, SLOT(addFunction()));
  connect(actionDeleteFunction, SIGNAL(triggered()), this, SLOT(deleteFunction()));
  connect(actionAddInputMessage, SIGNAL(triggered()), this, SLOT(addInputMessage()));
  connect(actionDeleteIOMessage, SIGNAL(triggered()), this, SLOT(deleteInputMessage()));
  connect(actionAddOutputMessage, SIGNAL(triggered()), this, SLOT(addOutputMessage()));
}

XModelView::~XModelView(){

}

void XModelView::setParentWindow(QWidget *parent){
  this->parentWidget = parent;
}

void XModelView::setModel(QAbstractItemModel * model){
  QTreeView::setModel(model);
  connect(this->selectionModel(),
		  SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
		  this, SLOT(itemActivated(const QModelIndex &, const QModelIndex&)));
}

void XModelView::contextMenuEvent(QContextMenuEvent * ev){
  QMenu menu(this);
  QModelIndex selected = this->currentIndex();

  if(!selected.isValid()){
 	menu.addAction(actionAddModel);
  }
  else{
	QObject * selectedObject = (QObject*)selected.internalPointer();
	switch (XModelTree::getXMNodeType(selectedObject)) {
	case (XM::XModel): // XMODEL
	  XModel *model;
	  model = XModelTree::toXModel(selectedObject);
	  if(model->getParent()){
		menu.addAction(actionDeleteModel);
		menu.addAction(actionEnableModel);
		menu.addAction(actionDisableModel);
	  }
	  else{
		menu.addAction(actionDeleteModel);
	  }
	  break;
	case (XM::XModelList): // XMODELLIST
	  menu.addAction(actionAddModel);
	  break;
	case (XM::XEnvironment): // XENVIRONMENT
	  return;
	case (XM::XFile): // XFILE
	  menu.addAction(actionDeleteFunctionFile);
	  break;
	case (XM::XFileList): // XFILELIST
	  menu.addAction(actionAddFunctionFile);
	  break;
	case (XM::XTimeUnit): // XTIMEUNIT
	  menu.addAction(actionDeleteTimeUnit);
	  break;
	case (XM::XTimeUnitList): // XTIMEUNITLIST
	  menu.addAction(actionAddTimeUnit);
	  break;
	case (XM::XDataType): // XDATATYPE
	  menu.addAction(actionDeleteDataType);
	  break;
	case (XM::XDataTypeList): // XDATATYPELIST
	  menu.addAction(actionAddDataType);
	  break;
	case (XM::XAgent): // XAGENT
	  menu.addAction(actionDeleteAgent);
	  break;
	case (XM::XAgentList): // XAGENTLIST
	  menu.addAction(actionAddAgent);
	  break;
	case (XM::XMessage): // XMESSAGE
	  menu.addAction(actionDeleteMessage);
	  break;
	case (XM::XIOMessage): // XIOMESSAGE
	  menu.addAction(actionDeleteIOMessage);
	  break;
	case (XM::XMessageList): // XMESSAGELIST
	  menu.addAction(actionAddMessage);
	  break;
	case (XM::XInMessageList): // XINMESSAGELIST
	  menu.addAction(actionAddInputMessage);
	  break;
	case (XM::XOutMessageList): // XOUTMESSAGELIST
	  menu.addAction(actionAddOutputMessage);
	  break;
	case (XM::XVariable): // XVARIABLE
	  menu.addAction(actionDeleteVariable);
	  break;
	case (XM::XVariableList): // XVARIABLELIST
	  menu.addAction(actionAddVariable);
	  break;
	case (XM::XFunction): // XFUNCTION
	  menu.addAction(actionDeleteFunction);
	  break;
	case (XM::XFunctionList): // XFUNCTIONLIST
	  menu.addAction(actionAddFunction);
	  break;
	default: // XNOTHING or SIMPLY NOT RECOGNIZED
	  return;
	}
  }
  menu.exec(mapToGlobal(ev->pos()));
}

void XModelView::itemActivated(const QModelIndex & newI,
							   const QModelIndex & /* oldI */){
  if(!newI.isValid()){
	((XMMEMainWindow*)this->parentWidget)->showInfo("Unknown Item Activated [-1]");
  }
  
  // Display XMML
  this->displayXMML(newI);
  this->showEditWidget(newI);
}

void XModelView::displayXMML(const QModelIndex &index){
  // Look at which class of item is activated and
  // than take the corresponding information/edit activity
  QObject * activatedItem = static_cast<QObject *>(index.internalPointer());
  if(XModelTree::isXModel(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXModel(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXModelList(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXModelList(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXAgent(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXAgent(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXAgentList(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXAgentList(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXVariable(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXVariable(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXVariableList(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXVariableList(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXFunction(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXFunction(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXFunctionList(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXFunctionList(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXDataType(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXDataType(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXDataTypeList(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXDataTypeList(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXEnvironment(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXEnvironment(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXFileList(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXFileList(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXInMessageList(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXInMessageList(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXOutMessageList(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXOutMessageList(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXMessage(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXMessage(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXMessageList(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXMessageList(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXTimeUnit(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXTimeUnit(activatedItem)->toDomDocument().toString());
  }
  else if(XModelTree::isXTimeUnitList(activatedItem)){
	((XMMEMainWindow*)this->parentWidget)->showInfo(XModelTree::toXTimeUnitList(activatedItem)->toDomDocument().toString());
  }
  else{
	((XMMEMainWindow*)this->parentWidget)->showInfo("No XMML description available");
  }
}

void XModelView::showEditWidget(const QModelIndex &index){
  // Look at which class of item is activated and
  // than take the corresponding information/edit activity
  QObject * activatedItem = static_cast<QObject *>(index.internalPointer());
  if(XModelTree::isXModel(activatedItem)){
	XModel *model = XModelTree::toXModel(activatedItem);
	((XMMEMainWindow*)this->parentWidget)->editModel(model, index);
	return;
  }
  else if(XModelTree::isXModelList(activatedItem)){
	XModelList *modelList = XModelTree::toXModelList(activatedItem);
  }
  else if(XModelTree::isXAgent(activatedItem)){
	XAgent *agent = XModelTree::toXAgent(activatedItem);
	((XMMEMainWindow*)this->parentWidget)->editAgent(agent, index);
	return;
  }
  else if(XModelTree::isXAgentList(activatedItem)){
	XAgentList *agentList = XModelTree::toXAgentList(activatedItem);
  }
  else if(XModelTree::isXVariable(activatedItem)){
	XVariable *variable = XModelTree::toXVariable(activatedItem);
	((XMMEMainWindow*)this->parentWidget)->editVariable(variable, index);
	return;
  }
  else if(XModelTree::isXVariableList(activatedItem)){
	XVariableList *variableList = XModelTree::toXVariableList(activatedItem);
  }
  else if(XModelTree::isXFunction(activatedItem)){
	XFunction *function = XModelTree::toXFunction(activatedItem);
	((XMMEMainWindow*)this->parentWidget)->editFunction(function, index);
	return;
  }
  else if(XModelTree::isXFunctionList(activatedItem)){
	XFunctionList *functionList = XModelTree::toXFunctionList(activatedItem);
  }
  else if(XModelTree::isXDataType(activatedItem)){
	XDataType *dataType = XModelTree::toXDataType(activatedItem);
	((XMMEMainWindow*)this->parentWidget)->editDataType(dataType, index);
	return;
  }
  else if(XModelTree::isXDataTypeList(activatedItem)){
	XDataTypeList *dataTypeList = XModelTree::toXDataTypeList(activatedItem);
  }
  else if(XModelTree::isXEnvironment(activatedItem)){
	XEnvironment *environment = XModelTree::toXEnvironment(activatedItem);
  }
  else if(XModelTree::isXFile(activatedItem)){
	XFile *file = XModelTree::toXFile(activatedItem);
	((XMMEMainWindow*)this->parentWidget)->editFile(file, index);
	return;
  }
  else if(XModelTree::isXFileList(activatedItem)){
	XFileList *fileList = XModelTree::toXFileList(activatedItem);
  }
  else if(XModelTree::isXInMessageList(activatedItem)){
	XInMessageList *inMessageList = XModelTree::toXInMessageList(activatedItem);
	((XMMEMainWindow*)this->parentWidget)->editInputMessages(inMessageList, index);
	return;
  }
  else if(XModelTree::isXOutMessageList(activatedItem)){
	XOutMessageList *outMessageList = XModelTree::toXOutMessageList(activatedItem);
	((XMMEMainWindow*)this->parentWidget)->editOutputMessages(outMessageList, index);
	return; 
  }
  else if(XModelTree::isXMessage(activatedItem)){
	XMessage *message = XModelTree::toXMessage(activatedItem);
	((XMMEMainWindow*)this->parentWidget)->editMessage(message, index);
	return;
  }
  else if(XModelTree::isXIOMessage(activatedItem)){
	XIOMessage *IOmessage = XModelTree::toXIOMessage(activatedItem);
	if(XModelTree::isXInMessageList(IOmessage->parent)){
	  ((XMMEMainWindow*)this->parentWidget)->editIOMessage(IOmessage, index);
	}
	return;
  }
  else if(XModelTree::isXMessageList(activatedItem)){
	XMessageList *messageList = XModelTree::toXMessageList(activatedItem);
  }
  else if(XModelTree::isXTimeUnit(activatedItem)){
	XTimeUnit *timeUnit = XModelTree::toXTimeUnit(activatedItem);
	((XMMEMainWindow*)this->parentWidget)->editTimeUnit(timeUnit, index);
	return;
  }
  else if(XModelTree::isXTimeUnitList(activatedItem)){
	XTimeUnitList *timeUnitList = XModelTree::toXTimeUnitList(activatedItem);
  }
  ((XMMEMainWindow*)this->parentWidget)->editNull();
}

void XModelView::addModel(){
  QModelIndex selected = this->currentIndex();

  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XModelList * modelList = XModelTree::toXModelList((QObject*)selected.internalPointer());
	qDebug() << modelList->modelList;
	XModel *model = new XModel(modelList);
	model->setName("New Model");
	modelList->modelList << model;
	this->model()->setData(selected, QVariant());
	this->collapse(selected);
	this->expand(selected);
  }
}

void XModelView::deleteModel(){
  QModelIndex selected = this->currentIndex();
  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XModel * model = XModelTree::toXModel((QObject*)selected.internalPointer());
	if(model){
	  if(model->getParent()){
		int index = model->getParent()->modelList.indexOf(model);
		if(index >= 0){
		  XModel *item = model->getParent()->modelList.takeAt(index);
		  qDebug() << "Item deleted from the model list";
		  // TODO: Delete the XModel.
		  this->collapse(selected.parent());
		  this->expand(selected.parent());
		}
		else{
		  qDebug() << "Item not found in the model list";
		}
	  }
	  else{
		qDebug() << "Top level model cannot be deleted.";
	  }
	}
	else{
	  qDebug() << "Nothing selected.";
	}
  }
}

void XModelView::enableModel(){
  QModelIndex selected = this->currentIndex();

  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XModel * model = XModelTree::toXModel((QObject*)selected.internalPointer());
	model->setEnabled(true);
	this->model()->setData(selected, QVariant());
  }
}

void XModelView::disableModel(){
  QModelIndex selected = this->currentIndex();

  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XModel * model = XModelTree::toXModel((QObject*)selected.internalPointer());
	model->setEnabled(false);
	this->model()->setData(selected, QVariant());
  }
}

void XModelView::addAgent(){
  QModelIndex selected = this->currentIndex();

  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XAgentList * agentList = XModelTree::toXAgentList((QObject*)selected.internalPointer());
	qDebug() << agentList->agentList;
	XAgent *agent = new XAgent(agentList);
	agent->setName("New Agent");
	agentList->agentList << agent;
	this->model()->setData(selected, QVariant());
	this->collapse(selected);
	this->expand(selected);
  }
}

void XModelView::deleteAgent(){
  QModelIndex selected = this->currentIndex();
  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XAgent * agent = XModelTree::toXAgent((QObject*)selected.internalPointer());
	if(agent){
	  if(agent->getParent()){
		int index = agent->getParent()->agentList.indexOf(agent);
		if(index >= 0){
		  XAgent *item = agent->getParent()->agentList.takeAt(index);
		  qDebug() << "Item deleted from the agent list";
		  // TODO: Delete the XAgent.
		  this->collapse(selected.parent());
		  this->expand(selected.parent());
		}
		else{
		  qDebug() << "Item not found in the agent list";
		}
	  }
	  else{
		qDebug() << "Top level agent cannot be deleted.";
	  }
	}
	else{
	  qDebug() << "Nothing selected.";
	}
  }
}

void XModelView::addMessage(){
  QModelIndex selected = this->currentIndex();

  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XMessageList * messageList = XModelTree::toXMessageList((QObject*)selected.internalPointer());
	qDebug() << messageList->messageList;
	XMessage *message = new XMessage(messageList);
	message->setName("New Message");
	messageList->messageList << message;
	this->model()->setData(selected, QVariant());
	this->collapse(selected);
	this->expand(selected);
  }
}

void XModelView::deleteMessage(){
  QModelIndex selected = this->currentIndex();
  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XMessage * message = XModelTree::toXMessage((QObject*)selected.internalPointer());
	if(message){
	  if(message->getParent()){
		int index = message->getParent()->messageList.indexOf(message);
		if(index >= 0){
		  XMessage *item = message->getParent()->messageList.takeAt(index);
		  qDebug() << "Item deleted from the message list";
		  // TODO: Delete the XMessage.
		  this->collapse(selected.parent());
		  this->expand(selected.parent());
		}
		else{
		  qDebug() << "Item not found in the message list";
		}
	  }
	  else{
		qDebug() << "Top level message cannot be deleted.";
	  }
	}
	else{
	  qDebug() << "Nothing selected.";
	}
  }
}

void XModelView::addConstant(){ // TODO: To be implemented
  // TODO: Does not enter here
}

void XModelView::deleteConstant(){ // TODO: To be converted to Variable
  deleteVariable();
}

void XModelView::addFunctionFile(){
  QModelIndex selected = this->currentIndex();

  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XFileList * fileList = XModelTree::toXFileList((QObject*)selected.internalPointer());
	qDebug() << fileList->fileList;
	XFile *file = new XFile(fileList);
	fileList->fileList << file;
	this->model()->setData(selected, QVariant());

	this->collapse(selected);
	this->expand(selected);
  }
}

void XModelView::deleteFunctionFile(){
  QModelIndex selected = this->currentIndex();
  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XFile * file = XModelTree::toXFile((QObject*)selected.internalPointer());
	if(file){
	  if(file->getParent()){
		int index = file->getParent()->fileList.indexOf(file);
		if(index >= 0){
		  XFile *item = file->getParent()->fileList.takeAt(index);
		  qDebug() << "Item deleted from the file list";
		  // TODO: Delete the XFile.
		  this->collapse(selected.parent());
		  this->expand(selected.parent());
		}
		else{
		  qDebug() << "Item not found in the file list";
		}
	  }
	  else{
		qDebug() << "Top level file cannot be deleted.";
	  }
	}
	else{
	  qDebug() << "Nothing selected.";
	}
  }
}

void XModelView::addTimeUnit(){
  QModelIndex selected = this->currentIndex();

  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XTimeUnitList * timeUnitList = XModelTree::toXTimeUnitList((QObject*)selected.internalPointer());
	qDebug() << timeUnitList->timeUnitList;
	XTimeUnit *timeUnit = new XTimeUnit(timeUnitList);
	timeUnit->setName("New Time Unit");
	timeUnitList->timeUnitList << timeUnit;
	this->model()->setData(selected, QVariant());
	this->collapse(selected);
	this->expand(selected);
  }
}

void XModelView::deleteTimeUnit(){
  QModelIndex selected = this->currentIndex();
  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XTimeUnit * timeUnit = XModelTree::toXTimeUnit((QObject*)selected.internalPointer());
	if(timeUnit){
	  if(timeUnit->getParent()){
		int index = timeUnit->getParent()->timeUnitList.indexOf(timeUnit);
		if(index >= 0){
		  XTimeUnit *item = timeUnit->getParent()->timeUnitList.takeAt(index);
		  qDebug() << "Item deleted from the timeUnit list";
		  // TODO: Delete the XTimeUnit.
		  this->collapse(selected.parent());
		  this->expand(selected.parent());
		}
		else{
		  qDebug() << "Item not found in the timeUnit list";
		}
	  }
	  else{
		qDebug() << "Top level timeUnit cannot be deleted.";
	  }
	}
	else{
	  qDebug() << "Nothing selected.";
	}
  }
}

void XModelView::addDataType(){
  QModelIndex selected = this->currentIndex();

  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XDataTypeList * dataTypeList = XModelTree::toXDataTypeList((QObject*)selected.internalPointer());
	qDebug() << dataTypeList->dataTypeList;
	XDataType *dataType = new XDataType(dataTypeList);
	dataType->setName("New Data Type");
	dataTypeList->dataTypeList << dataType;
	this->model()->setData(selected, QVariant());
	this->collapse(selected);
	this->expand(selected);
  }
}

void XModelView::deleteDataType(){
  QModelIndex selected = this->currentIndex();
  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XDataType * dataType = XModelTree::toXDataType((QObject*)selected.internalPointer());
	if(dataType){
	  if(dataType->getParent()){
		int index = dataType->getParent()->dataTypeList.indexOf(dataType);
		if(index >= 0){
		  XDataType *item = dataType->getParent()->dataTypeList.takeAt(index);
		  qDebug() << "Item deleted from the dataType list";
		  // TODO: Delete the XDataType.
		  this->collapse(selected.parent());
		  this->expand(selected.parent());
		}
		else{
		  qDebug() << "Item not found in the dataType list";
		}
	  }
	  else{
		qDebug() << "Top level dataType cannot be deleted.";
	  }
	}
	else{
	  qDebug() << "Nothing selected.";
	}
  }
}

void XModelView::addVariable(){
  QModelIndex selected = this->currentIndex();

  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XVariableList * variableList = XModelTree::toXVariableList((QObject*)selected.internalPointer());
	qDebug() << variableList->variableList;
	XVariable *variable = new XVariable(variableList);
	variable->setName("New Item");
	variableList->variableList << variable;
	this->model()->setData(selected, QVariant());
	this->collapse(selected);
	this->expand(selected);
  }
}

void XModelView::deleteVariable(){
  QModelIndex selected = this->currentIndex();
  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XVariable * variable = XModelTree::toXVariable((QObject*)selected.internalPointer());
	if(variable){
	  if(variable->getParent()){
		int index = variable->getParent()->variableList.indexOf(variable);
		if(index >= 0){
		  XVariable *item = variable->getParent()->variableList.takeAt(index);
		  qDebug() << "Item deleted from the variable list";
		  // TODO: Delete the XVariable.
		  this->collapse(selected.parent());
		  this->expand(selected.parent());
		}
		else{
		  qDebug() << "Item not found in the variable list";
		}
	  }
	  else{
		qDebug() << "Top level variable cannot be deleted.";
	  }
	}
	else{
	  qDebug() << "Nothing selected.";
	}
  }
}

void XModelView::addFunction(){
  QModelIndex selected = this->currentIndex();

  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XFunctionList * functionList = XModelTree::toXFunctionList((QObject*)selected.internalPointer());
	qDebug() << functionList->functionList;
	XFunction *function = new XFunction(functionList);
	function->setName("New Function");
	functionList->functionList << function;
	this->model()->setData(selected, QVariant());
	this->collapse(selected);
	this->expand(selected);
  }
}

void XModelView::deleteFunction(){
  QModelIndex selected = this->currentIndex();
  if(!selected.isValid()){
	qDebug() << "No selection";
  }
  else{
	XFunction * function = XModelTree::toXFunction((QObject*)selected.internalPointer());
	if(function){
	  if(function->getParent()){
		int index = function->getParent()->functionList.indexOf(function);
		if(index >= 0){
		  XFunction *item = function->getParent()->functionList.takeAt(index);
		  qDebug() << "Item deleted from the function list";
		  // TODO: Delete the XFunction.
		  this->collapse(selected.parent());
		  this->expand(selected.parent());
		}
		else{
		  qDebug() << "Item not found in the function list";
		}
	  }
	  else{
		qDebug() << "Top level function cannot be deleted.";
	  }
	}
	else{
	  qDebug() << "Nothing selected.";
	}
  }
}

void XModelView::addInputMessage(){ // TODO: To be implemented

}

void XModelView::deleteInputMessage(){ // TODO: To be implemented

}

void XModelView::addOutputMessage(){ // TODO: To be implemented

}

void XModelView::deleteOutputMessage(){ // TODO: To be implemented

}
