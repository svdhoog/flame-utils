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

#include <qcolor.h>
#include <qdatetime.h>
#include <qdebug.h>
#include <qfont.h>
#include <qicon.h>

#include "XModelTree.h"

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


XModelTree::XModelTree(XModel *rootItem){
  this->rootItem = rootItem;
  this->nothing = new XNothing;
}

XModelTree::~XModelTree(){
  
}

/////////////////////////////////////////
// NAVIGATION AND MODEL INDEX CREATION //
/////////////////////////////////////////

///////////////////////////////////////////////////
// NAVIGATION AND MODEL INDEX CREATION: Children //
///////////////////////////////////////////////////

QModelIndex XModelTree::index(int row, int column, const QModelIndex & parent) const {

  if (!hasIndex(row, column, parent))
	return QModelIndex();

  if(!parent.isValid()) {
	if(row == 0){
	  return createIndex(row, column, this->rootItem);
	}
	else{
	  return QModelIndex();
	}
  }

  // Get the object pointer at index.
  QObject* objAtInd = this->itemFromIndex(parent);
  
  //////////////////////
  // CHECK: TOP LEVEL //
  //////////////////////
  //if(this->isTopLevel(objAtInd)){
  //return createIndex(row, column, this->rootItem);
  //}

  // Check for the type of the node at index. Take corresponding
  // action then.
  switch (this->getXMNodeType(objAtInd)) {
  case (XM::XModel): // XMODEL
	XModel* model;
	model = this->toXModel(objAtInd);
	if(row == 0){
	  return createIndex(row, column, model->getNestedModels());
	}
	else if(row == 1){
	  return createIndex(row, column, model->getAgents());
	}	
	else if(row == 2){
	  return createIndex(row, column, model->getMessages());
	}	
	else{
	  return createIndex(row, column, model->getEnvironment());
	}	
  case (XM::XModelList): // XMODELLIST
	XModelList* modelList;
	modelList = this->toXModelList(objAtInd);
	return createIndex(row, column, modelList->modelList.at(row));
  case (XM::XTimeUnitList): // XTIMEUNITLIST
	XTimeUnitList* timeUnitList;
	timeUnitList = this->toXTimeUnitList(objAtInd);
	return createIndex(row, column, timeUnitList->timeUnitList.at(row));
  case (XM::XDataTypeList): // XTIMEUNITLIST
	XDataTypeList* dataTypeList;
	dataTypeList = this->toXDataTypeList(objAtInd);
	return createIndex(row, column, dataTypeList->dataTypeList.at(row));
  case (XM::XEnvironment): // XMODEL
	XEnvironment* environment;
	environment = this->toXEnvironment(objAtInd);
	if(row == 0){
	  return createIndex(row, column, environment->getConstants());
	}
	else if(row == 1){
	  return createIndex(row, column, environment->getFunctionFiles());
	}
	else if(row == 2){
	  return createIndex(row, column, environment->getTimeUnitList());
	}
	else if(row == 3){
	  return createIndex(row, column, environment->getDataTypes());
	}
  case (XM::XAgent): // XAGENT
	XAgent* agent;
	agent = this->toXAgent(objAtInd);
	if(row == 0){
	  return createIndex(row, column, agent->getVariables());
	}
	else{
	  return createIndex(row, column, agent->getFunctions());
	}
  case (XM::XAgentList): // XMODELLIST
	XAgentList* agentList;
	agentList = this->toXAgentList(objAtInd);
	return createIndex(row, column, agentList->agentList.at(row));
  case (XM::XMessage): // XMODEL
	XMessage* message;
	message = this->toXMessage(objAtInd);
	return createIndex(row, column, message->getVariables());
  case (XM::XDataType): // XMODEL
	XDataType* dataType;
	dataType = this->toXDataType(objAtInd);
	return createIndex(row, column, dataType->getVariables());
  case (XM::XMessageList): // XMESSAGELIST
	XMessageList* messageList;
	messageList = this->toXMessageList(objAtInd);
	return createIndex(row, column, messageList->messageList.at(row));
  case (XM::XInMessageList): // XMESSAGELIST
	XInMessageList* inMessageList;
	inMessageList = this->toXInMessageList(objAtInd);
	return createIndex(row, column, inMessageList->messageList.at(row));
  case (XM::XOutMessageList): // XMESSAGELIST
	XOutMessageList* outMessageList;
	outMessageList = this->toXOutMessageList(objAtInd);
	return createIndex(row, column, outMessageList->messageList.at(row));
  case (XM::XVariableList): // XVARIABLELIST
	XVariableList* variableList;
	variableList = this->toXVariableList(objAtInd);
	return createIndex(row, column, variableList->variableList.at(row));
  case (XM::XFileList): // XFILELIST
	XFileList* fileList;
	fileList = this->toXFileList(objAtInd);
	return createIndex(row, column, fileList->fileList.at(row));
  case (XM::XFunctionList): // XFUNCTIONLIST
	XFunctionList* functionList;
	functionList = this->toXFunctionList(objAtInd);
	return createIndex(row, column, functionList->functionList.at(row));
  case (XM::XFunction): // XFUNCTION
	XFunction* function;
	function = this->toXFunction(objAtInd);
	if(row == 0){
	  return createIndex(row, column, function->messagesIn);
	}
	else {
	  return createIndex(row, column, function->messagesOut);
	}
  default: // XNOTHING or SIMPLY NOT RECOGNIZED
	return QModelIndex();
  }
}

//////////////////////////////////////////////////
// NAVIGATION AND MODEL INDEX CREATION: Parents //
//////////////////////////////////////////////////

QModelIndex XModelTree::parent(const QModelIndex & index) const {
  if(!index.isValid()) {
	return QModelIndex();
  }

  // Get the object pointer at index.
  QObject* objAtInd = this->itemFromIndex(index);
  
  if(!objAtInd){
	return QModelIndex();
  }
  
  // Check for the type of the node at index. Take corresponding
  // action then.
  switch (this->getXMNodeType(objAtInd)) {
  case (XM::XModel): // XMODEL
	XModel* model;
	model = this->toXModel(objAtInd);
	if(model->getParent()){
	  return createIndex(0, 0, model->getParent());
	}
	else{
	  return QModelIndex();
	}
  case (XM::XModelList): // XMODELLIST
	XModelList* modelList;
	modelList = this->toXModelList(objAtInd);
	if(modelList->getParent() && modelList->getParent()->getParent()){
	  return createIndex(modelList->getParent()->getParent()->modelList.indexOf(modelList->getParent()), 0, modelList->getParent()); // scary, huh?
	}
	else if(modelList->getParent()){
	  return createIndex(0, 0, modelList->getParent());
	}
	else{
	  return QModelIndex();
	}
  case (XM::XEnvironment): // XENVIRONMENT
	XEnvironment* environment;
	environment = this->toXEnvironment(objAtInd);
	if(environment->getParent() && environment->getParent()->getParent()){
	  return createIndex(environment->getParent()->getParent()->modelList.indexOf(environment->getParent()), 0, environment->getParent()); // scary, huh?
	}
	else if(environment->getParent()){
	  return createIndex(0, 0, environment->getParent());
	}
	else{
	  return QModelIndex();
	}
  case (XM::XAgent): // XAGENT
	XAgent* agent;
	agent = this->toXAgent(objAtInd);
	if(agent->getParent() && agent->getParent()->getParent()){
	  return createIndex(1, 0, agent->getParent());
	}
	else if(agent->getParent()){
	  return createIndex(0, 0, agent->getParent());
	}
	else{
	  return QModelIndex();
	}
  case (XM::XAgentList): // XAGENTLIST
	XAgentList* agentList;
	agentList = this->toXAgentList(objAtInd);
	if(agentList->getParent() && agentList->getParent()->getParent()){
	  return createIndex(agentList->getParent()->getParent()->modelList.indexOf(agentList->getParent()), 0, agentList->getParent()); // scary, huh?
	}
	else if(agentList->getParent()){
	  return createIndex(0, 0, agentList->getParent());
	}
	else{
	  return QModelIndex();
	}
  case (XM::XMessage): // XMESSAGE
	XMessage* message;
	message = this->toXMessage(objAtInd);
	if(message->getParent() && message->getParent()->getParent()){
	  return createIndex(2, 0, message->getParent());
	}
	else if(message->getParent()){
	  return createIndex(0, 0, message->getParent());
	}
	else{
	  return QModelIndex();
 	}
  case (XM::XIOMessage): // XIOMESSAGE
	XIOMessage* IOmessage;
	IOmessage = this->toXIOMessage(objAtInd);
	if(IOmessage->parent){
	  if(XModelTree::isXInMessageList(IOmessage->parent)){
		return createIndex(0, 0, IOmessage->parent);
	  }
	  else{
		return createIndex(1, 0, IOmessage->parent);
	  }
	}
	else{
	  return QModelIndex();
 	}
  case (XM::XMessageList): // XMESSAGELIST
	XMessageList* messageList;
	messageList = this->toXMessageList(objAtInd);
	if(messageList->getParent() && messageList->getParent()->getParent()){
	  return createIndex(messageList->getParent()->getParent()->modelList.indexOf(messageList->getParent()), 0, messageList->getParent()); // scary, huh?
	}
	else if(messageList->getParent()){
	  return createIndex(0, 0, messageList->getParent());
	}
	else{
	  return QModelIndex();
	}
  case (XM::XInMessageList): // XMESSAGELIST
	XInMessageList* inMessageList;
	inMessageList = this->toXInMessageList(objAtInd);
	if(inMessageList->getParent() && inMessageList->getParent()->getParent()){
	  return createIndex(inMessageList->getParent()->getParent()->functionList.indexOf(inMessageList->getParent()), 0, inMessageList->getParent()); // scary, huh?
	}
	else if(inMessageList->getParent()){
	  return createIndex(0, 0, inMessageList->getParent());
	}
	else{
	  return QModelIndex();
	}
  case (XM::XOutMessageList): // XMESSAGELIST
	XOutMessageList* outMessageList;
	outMessageList = this->toXOutMessageList(objAtInd);
	if(outMessageList->getParent() && outMessageList->getParent()->getParent()){
	  return createIndex(outMessageList->getParent()->getParent()->functionList.indexOf(outMessageList->getParent()), 0, outMessageList->getParent()); // scary, huh?
	}
	else if(outMessageList->getParent()){
	  return createIndex(0, 0, outMessageList->getParent());
	}
	else{
	  return QModelIndex();
	}
  case (XM::XVariable): // XVARIABLE
	XVariable* variable;
	variable = this->toXVariable(objAtInd);
	if(variable->getParent() && variable->getParent()->getParent()){
	  return createIndex(0, 0, variable->getParent());
	}
	else if(variable->getParent()){
	  return createIndex(0, 0, variable->getParent());
	}
	else{
	  return QModelIndex();
 	}
  case (XM::XFile): // XFILE
	XFile* file;
	file = this->toXFile(objAtInd);
	if(file->getParent() && file->getParent()->getParent()){
	  return createIndex(1, 0, file->getParent());
	}
	else if(file->getParent()){
	  return createIndex(0, 0, file->getParent());
	}
	else{
	  return QModelIndex();
 	}
  case (XM::XTimeUnit): // XTIMEUNIT
	XTimeUnit* timeUnit;
	timeUnit = this->toXTimeUnit(objAtInd);
	if(timeUnit->getParent() && timeUnit->getParent()->getParent()){
	  return createIndex(2, 0, timeUnit->getParent());
	}
	else if(timeUnit->getParent()){
	  return createIndex(0, 0, timeUnit->getParent());
	}
	else{
	  return QModelIndex();
 	}
  case (XM::XDataType): // XTIMEUNIT
	XDataType* dataType;
	dataType = this->toXDataType(objAtInd);
	if(dataType->getParent() && dataType->getParent()->getParent()){
	  return createIndex(3, 0, dataType->getParent());
	}
	else if(dataType->getParent()){
	  return createIndex(0, 0, dataType->getParent());
	}
	else{
	  return QModelIndex();
 	}
  case (XM::XVariableList): // XVARIABLELIST
	XVariableList* variableList;
	variableList = this->toXVariableList(objAtInd);
	if(this->isXAgent(variableList->getParent())){
	  XAgent *agent = this->toXAgent(variableList->getParent());
	  if(variableList->getParent() && agent->getParent()){
		return createIndex(agent->getParent()->agentList.indexOf(agent), 0, agent);
	  }
	  else if(variableList->getParent()){
		return createIndex(0, 0, agent);
	  }
	}
	else if(this->isXMessage(variableList->getParent())){
	  XMessage *message = this->toXMessage(variableList->getParent());
	  if(variableList->getParent() && message->getParent()){
		return createIndex(message->getParent()->messageList.indexOf(message), 0, message);
	  }
	  else if(variableList->getParent()){
		return createIndex(0, 0, message);
	  }
	}
	else if(this->isXEnvironment(variableList->getParent())){
	  XEnvironment *environment = this->toXEnvironment(variableList->getParent());
	  if(variableList->getParent() && environment->getParent()){
		return createIndex(3, 0, environment);
	  }
	  else if(variableList->getParent()){
		return createIndex(0, 0, environment);
	  }
	}
	else if(this->isXDataType(variableList->getParent())){
	  XDataType *dt = this->toXDataType(variableList->getParent());
	  if(variableList->getParent() && dt->getParent()){
		return createIndex(dt->getParent()->dataTypeList.indexOf(dt), 0, dt);
	  }
	  else if(variableList->getParent()){
		return createIndex(0, 0, environment);
	  }
	}
	else{
	  return QModelIndex();
	}
  case (XM::XFileList): // XFileList
	XFileList* fileList;
	fileList = this->toXFileList(objAtInd);
	if(this->isXEnvironment(fileList->getParent())){
	  XEnvironment *environment = this->toXEnvironment(fileList->getParent());
	  if(fileList->getParent() && environment->getParent()){
		return createIndex(3, 0, environment);
	  }
	  else if(fileList->getParent()){
		return createIndex(0, 0, environment);
	  }
	}
	else{
	  return QModelIndex();
	}
  case (XM::XTimeUnitList): // XTimeUnitList
	XTimeUnitList* timeUnitList;
	timeUnitList = this->toXTimeUnitList(objAtInd);
	if(this->isXEnvironment(timeUnitList->getParent())){
	  XEnvironment *environment = this->toXEnvironment(timeUnitList->getParent());
	  if(timeUnitList->getParent() && environment->getParent()){
		return createIndex(3, 0, environment);
	  }
	  else if(timeUnitList->getParent()){
		return createIndex(0, 0, environment);
	  }
	}
	else{
	  return QModelIndex();
	}
  case (XM::XDataTypeList): // XDataTypeList
	XDataTypeList* dataTypeList;
	dataTypeList = this->toXDataTypeList(objAtInd);
	if(this->isXEnvironment(dataTypeList->getParent())){
	  XEnvironment *environment = this->toXEnvironment(dataTypeList->getParent());
	  if(dataTypeList->getParent() && environment->getParent()){
		return createIndex(3, 0, environment);
	  }
	  else if(dataTypeList->getParent()){
		return createIndex(0, 0, environment);
	  }
	}
	else{
	  return QModelIndex();
	}
  case (XM::XFunction): // XFUNCTION
	XFunction* function;
	function = this->toXFunction(objAtInd);
	if(function->getParent() && function->getParent()->getParent()){
	  return createIndex(1, 0, function->getParent());
	}
	else if(function->getParent()){
	  return createIndex(0, 0, function->getParent());
	}
	else{
	  return QModelIndex();
 	}
  case (XM::XFunctionList): // XFUNCTIONLIST
	XFunctionList* functionList;
	functionList = this->toXFunctionList(objAtInd);
	if(this->isXAgent(functionList->getParent())){
	  XAgent *agent = this->toXAgent(functionList->getParent());
	  if(functionList->getParent() && agent->getParent()){
		return createIndex(agent->getParent()->agentList.indexOf(agent), 0, agent);
	  }
	  else if(functionList->getParent()){
		return createIndex(0, 0, agent);
	  }
	}
	else{
	  return QModelIndex();
	}
  default: // XNOTHING or SIMPLY NOT RECOGNIZED
	return QModelIndex();
  }
}

////////////////////////
// ITEM DATA HANDLING //
////////////////////////

//////////////////////////////////////////
// ITEM DATA HANDLING: Read-Only Access //
//////////////////////////////////////////

// Qt::ItemFlags XModelTree::flags(const QModelIndex & index) const {

//   qDebug() << "Qt::ItemFlags XModelTree::flags(const QModelIndex & index) const";

//   // If the model index is not valid, no flags set.
//   if(!index.isValid()){
//   	return 0;
//   }

//   // Model is valid, go ahead.
//   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
// }

QVariant XModelTree::data(const QModelIndex & index, int role) const {
  // If the model index is not valid, nothing returned.
  if(!index.isValid()){
  	return QVariant();
  }

  // Get the object pointer at index.
  QObject* objAtInd = this->itemFromIndex(index);
  
  // Check for the type of the node at index. Take corresponding
  // action then.
  switch (this->getXMNodeType(objAtInd)) {
  case (XM::XModel): // XMODEL
	return this->dataForXModelWithRole(this->toXModel(objAtInd), role);
  case (XM::XModelList): // XMODELLIST
	return this->dataForXModelListWithRole(this->toXModelList(objAtInd), role);
  case (XM::XEnvironment): // XENVIRONMENT
	return this->dataForXEnvironmentWithRole(this->toXEnvironment(objAtInd), role);
  case (XM::XFile): // XFILE
	return this->dataForXFileWithRole(this->toXFile(objAtInd), role);
  case (XM::XFileList): // XFILELIST
	return this->dataForXFileListWithRole(this->toXFileList(objAtInd), role);
  case (XM::XTimeUnit): // XTIMEUNIT
	return this->dataForXTimeUnitWithRole(this->toXTimeUnit(objAtInd), role);
  case (XM::XTimeUnitList): // XTIMEUNITLIST
	return this->dataForXTimeUnitListWithRole(this->toXTimeUnitList(objAtInd), role);
  case (XM::XDataType): // XDATATYPE
	return this->dataForXDataTypeWithRole(this->toXDataType(objAtInd), role);
  case (XM::XDataTypeList): // XDATATYPELIST
	return this->dataForXDataTypeListWithRole(this->toXDataTypeList(objAtInd), role);
  case (XM::XAgent): // XAGENT
	return this->dataForXAgentWithRole(this->toXAgent(objAtInd), role);
  case (XM::XAgentList): // XAGENTLIST
	return this->dataForXAgentListWithRole(this->toXAgentList(objAtInd), role);
  case (XM::XMessage): // XMESSAGE
	return this->dataForXMessageWithRole(this->toXMessage(objAtInd), role);
  case (XM::XIOMessage): // XIOMESSAGE
	return this->dataForXIOMessageWithRole(this->toXIOMessage(objAtInd), role);
  case (XM::XMessageList): // XMESSAGELIST
	return this->dataForXMessageListWithRole(this->toXMessageList(objAtInd), role);
  case (XM::XInMessageList): // XINMESSAGELIST
	return this->dataForXInMessageListWithRole(this->toXInMessageList(objAtInd), role);
  case (XM::XOutMessageList): // XOUTMESSAGELIST
	return this->dataForXOutMessageListWithRole(this->toXOutMessageList(objAtInd), role);
  case (XM::XVariable): // XVARIABLE
	return this->dataForXVariableWithRole(this->toXVariable(objAtInd), role);
  case (XM::XVariableList): // XVARIABLELIST
	return this->dataForXVariableListWithRole(this->toXVariableList(objAtInd), role);
  case (XM::XFunction): // XFUNCTION
	return this->dataForXFunctionWithRole(this->toXFunction(objAtInd), role);
  case (XM::XFunctionList): // XFUNCTIONLIST
	return this->dataForXFunctionListWithRole(this->toXFunctionList(objAtInd), role);
  default: // XNOTHING or SIMPLY NOT RECOGNIZED
	return QVariant();
  }
}

QVariant XModelTree::headerData(int section, Qt::Orientation orientation, int role) const {
  // Only for the horizontal orientation and display role, show the
  // header according to the section.
  if(orientation == Qt::Horizontal && role == Qt::DisplayRole){
	if(section == 0){
	  return tr("Data");
	}
	else if(section == 1){
	  return tr("Value");
	}
  }
  // Use defaults inherited from the super class.
  return QAbstractItemModel::headerData(section, orientation, role);
}

int XModelTree::rowCount(const QModelIndex & parent) const {
  if (parent.column() > 0){
	return 0;
  }

  if (!parent.isValid()){
	return 1;
  }

  // Index is valid, extract the parent object.
  QObject *parentItem = itemFromIndex(parent);

  // Top level contains only one row: Root XModel class!
  if(this->isTopLevel(parentItem)){
	return 4;
  }
  else if(this->isXModel(parentItem)){
	return 4;
  }
  else if(this->isXModelList(parentItem)){
	XModelList * parentModelList = this->toXModelList(parentItem);
	return parentModelList->modelList.size();
  }
  else if(this->isXEnvironment(parentItem)){
	return 4;
  }
  else if(this->isXAgent(parentItem)){
	return 2;
  }
  else if(this->isXAgentList(parentItem)){
	XAgentList * parentAgentList = this->toXAgentList(parentItem);
	return parentAgentList->agentList.size();
  }
  else if(this->isXFileList(parentItem)){
	XFileList * parentFileList = this->toXFileList(parentItem);
	return parentFileList->fileList.size();
  }
  else if(this->isXTimeUnitList(parentItem)){
	XTimeUnitList * parentTimeUnitList = this->toXTimeUnitList(parentItem);
	return parentTimeUnitList->timeUnitList.size();
  }
  else if(this->isXDataTypeList(parentItem)){
	XDataTypeList * parentDataTypeList = this->toXDataTypeList(parentItem);
	return parentDataTypeList->dataTypeList.size();
  }
  else if(this->isXDataType(parentItem)){
	return 1;
  }
  else if(this->isXMessage(parentItem)){
	return 1;
  }
  else if(this->isXMessageList(parentItem)){
	XMessageList * parentMessageList = this->toXMessageList(parentItem);
	return parentMessageList->messageList.size();
  }
  else if(this->isXInMessageList(parentItem)){
	XInMessageList * parentInMessageList = this->toXInMessageList(parentItem);
	return parentInMessageList->messageList.size();
  }
  else if(this->isXOutMessageList(parentItem)){
	XOutMessageList * parentOutMessageList = this->toXOutMessageList(parentItem);
	return parentOutMessageList->messageList.size();
  }
  else if(this->isXVariableList(parentItem)){
	XVariableList * parentVariableList = this->toXVariableList(parentItem);
	return parentVariableList->variableList.size();
  }
  else if(this->isXFunction(parentItem)){
	return 2;
  }
  else if(this->isXFunctionList(parentItem)){
	XFunctionList * parentFunctionList = this->toXFunctionList(parentItem);
	return parentFunctionList->functionList.size();
  }
  return 0;
}

int XModelTree::columnCount(const QModelIndex & parent) const {
  // If the model index is not valid, no columns.
  return 1;
}

////////////////////////////////////////
// ITEM DATA HANDLING: Editable Items //
////////////////////////////////////////

bool XModelTree::setData(const QModelIndex & index,
						 const QVariant & /* value */,
						 int /* role */) {
  if(!index.isValid()){
	return false;
  }
  
  emit dataChanged(index, index);
  return true;
}

bool XModelTree::setHeaderData(int section, Qt::Orientation orientation, const QVariant & value, int role) {
  return false;
}

bool XModelTree::setItemData(const QModelIndex & index, const QMap<int, QVariant> & roles) {
  return false;
}

//////////////////////////////////////////
// ITEM DATA HANDLING: Resizable Models //
//////////////////////////////////////////

/////////////////////////////////////////////////
// ITEM DATA HANDLING: Resizable Models (Rows) //
/////////////////////////////////////////////////

bool XModelTree::insertRows(int row, int count, const QModelIndex & parent) {
  return false;
}

bool XModelTree::removeRows(int row, int count, const QModelIndex & parent) {
  return false;
}

bool XModelTree::removeRow(int row, const QModelIndex & parent) {
  return false;
}

////////////////////////////////////////////////////
// ITEM DATA HANDLING: Resizable Models (Columns) //
////////////////////////////////////////////////////

bool XModelTree::insertColumns(int column, int count, const QModelIndex & parent) {
  return false;
}

bool XModelTree::removeColumns(int column, int count, const QModelIndex & parent) {
  return false;
}

bool XModelTree::removeColumn(int column, const QModelIndex & parent) {
  return false;
}

///////////////////////////////////////////////////////
// ITEM DATA HANDLING: Lazy Population of Model Data //
///////////////////////////////////////////////////////

// bool XModelTree::hasChildren(const QModelIndex & parent) const {
//   return false;
// }

//////////////////////////////////////////////////
// DRAG AND DROP SUPPORT AND MIME TYPE HANDLING //
//////////////////////////////////////////////////

QMimeData * XModelTree::mimeData(const QModelIndexList & indexes) const {
  return NULL;
}

Qt::DropActions XModelTree::supportedDragActions() {
  return Qt::IgnoreAction;
}

bool XModelTree::dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent) {
  return false;
}

//////////////////////
// CUSTOM FUNCTIONS //
//////////////////////

////////////////////////////////////////////////////////
// CUSTOM FUNCTIONS: Checks for the internal pointers //
////////////////////////////////////////////////////////

QObject* XModelTree::itemFromIndex(const QModelIndex &index) const {
  // if the index is a valid index, return the QObject cast.
  if(index.isValid()){
	return static_cast<QObject *>(index.internalPointer());
  }
  // The index is not valid, we should know this.
  return this->nothing;
}

QString XModelTree::getClassName(QObject *obj) {
  // Extract the actual class name of the QObject instance consumed.
  return QString(obj->metaObject()->className());
}

XM::NodeType XModelTree::getXMNodeType(QObject *obj) {
  // Return corresponding node type for the class name.
  QString className = getClassName(obj);
  if(className == "XModel") {
	return XM::XModel;
  }
  else if(className == "XModelList") {
	return XM::XModelList;
  }
  else if(className == "XAgent") {
	return XM::XAgent;
  }
  else if(className == "XEnvironment") {
	return XM::XEnvironment;
  }
  else if(className == "XFile") {
	return XM::XFile;
  }
  else if(className == "XFileList") {
	return XM::XFileList;
  }
  else if(className == "XTimeUnit") {
	return XM::XTimeUnit;
  }
  else if(className == "XTimeUnitList") {
	return XM::XTimeUnitList;
  }
  else if(className == "XDataType") {
	return XM::XDataType;
  }
  else if(className == "XDataTypeList") {
	return XM::XDataTypeList;
  }
  else if(className == "XAgentList") {
	return XM::XAgentList;
  }
  else if(className == "XMessage") {
	return XM::XMessage;
  }
  else if(className == "XIOMessage") {
	return XM::XIOMessage;
  }
  else if(className == "XMessageList") {
	return XM::XMessageList;
  }
  else if(className == "XInMessageList") {
	return XM::XInMessageList;
  }
  else if(className == "XOutMessageList") {
	return XM::XOutMessageList;
  }
  else if(className == "XVariable") {
	return XM::XVariable;
  }
  else if(className == "XVariableList") {
	return XM::XVariableList;
  }
  else if(className == "XFunction") {
	return XM::XFunction;
  }
  else if(className == "XFunctionList") {
	return XM::XFunctionList;
  }
  return XM::XNothing;
}

bool XModelTree::isTopLevel(QObject *obj) {
  return getClassName(obj) == "XNothing";
}

bool XModelTree::isXModel(QObject *obj) {
  return getClassName(obj) == "XModel";
}

bool XModelTree::isXModelList(QObject *obj) {
  return getClassName(obj) == "XModelList";
}

bool XModelTree::isXEnvironment(QObject *obj) {
  return getClassName(obj) == "XEnvironment";
}

bool XModelTree::isXFile(QObject *obj) {
  return getClassName(obj) == "XFile";
}

bool XModelTree::isXFileList(QObject *obj) {
  return getClassName(obj) == "XFileList";
}

bool XModelTree::isXTimeUnit(QObject *obj) {
  return getClassName(obj) == "XTimeUnit";
}

bool XModelTree::isXTimeUnitList(QObject *obj) {
  return getClassName(obj) == "XTimeUnitList";
}

bool XModelTree::isXDataType(QObject *obj) {
  return getClassName(obj) == "XDataType";
}

bool XModelTree::isXDataTypeList(QObject *obj) {
  return getClassName(obj) == "XDataTypeList";
}

bool XModelTree::isXAgent(QObject *obj) {
  return getClassName(obj) == "XAgent";
}

bool XModelTree::isXAgentList(QObject *obj) {
  return getClassName(obj) == "XAgentList";
}

bool XModelTree::isXMessage(QObject *obj) {
  return getClassName(obj) == "XMessage";
}

bool XModelTree::isXIOMessage(QObject *obj) {
  return getClassName(obj) == "XIOMessage";
}

bool XModelTree::isXMessageList(QObject *obj) {
  return getClassName(obj) == "XMessageList";
}

bool XModelTree::isXInMessageList(QObject *obj) {
  return getClassName(obj) == "XInMessageList";
}

bool XModelTree::isXOutMessageList(QObject *obj) {
  return getClassName(obj) == "XOutMessageList";
}

bool XModelTree::isXVariable(QObject *obj) {
  return getClassName(obj) == "XVariable";
}

bool XModelTree::isXVariableList(QObject *obj) {
  return getClassName(obj) == "XVariableList";
}

bool XModelTree::isXFunction(QObject *obj) {
  return getClassName(obj) == "XFunction";
}

bool XModelTree::isXFunctionList(QObject *obj) {
  return getClassName(obj) == "XFunctionList";
}

bool XModelTree::isXTreeLabel(QObject *obj) {
  return getClassName(obj) == "XTreeLabel";
}

/////////////////////////////////////////////////////////////////
// CUSTOM FUNCTIONS: Convert to QObject's to original classes. //
/////////////////////////////////////////////////////////////////

XModel * XModelTree::toXModel(QObject *obj) {
  return static_cast<XModel *>(obj);
}

XModelList * XModelTree::toXModelList(QObject *obj) {
  return static_cast<XModelList *>(obj);
}

XEnvironment * XModelTree::toXEnvironment(QObject *obj) {
  return static_cast<XEnvironment *>(obj);
}

XFile * XModelTree::toXFile(QObject *obj) {
  return static_cast<XFile *>(obj);
}

XFileList * XModelTree::toXFileList(QObject *obj) {
  return static_cast<XFileList *>(obj);
}

XTimeUnit * XModelTree::toXTimeUnit(QObject *obj) {
  return static_cast<XTimeUnit *>(obj);
}

XTimeUnitList * XModelTree::toXTimeUnitList(QObject *obj) {
  return static_cast<XTimeUnitList *>(obj);
}

XDataType * XModelTree::toXDataType(QObject *obj) {
  return static_cast<XDataType *>(obj);
}

XDataTypeList * XModelTree::toXDataTypeList(QObject *obj) {
  return static_cast<XDataTypeList *>(obj);
}

XAgent * XModelTree::toXAgent(QObject *obj) {
  return static_cast<XAgent *>(obj);
}

XAgentList * XModelTree::toXAgentList(QObject *obj) {
  return static_cast<XAgentList *>(obj);
}

XMessage * XModelTree::toXMessage(QObject *obj) {
  return static_cast<XMessage *>(obj);
}

XIOMessage * XModelTree::toXIOMessage(QObject *obj) {
  return static_cast<XIOMessage *>(obj);
}

XMessageList * XModelTree::toXMessageList(QObject *obj) {
  return static_cast<XMessageList *>(obj);
}

XInMessageList * XModelTree::toXInMessageList(QObject *obj) {
  return static_cast<XInMessageList *>(obj);
}

XOutMessageList * XModelTree::toXOutMessageList(QObject *obj) {
  return static_cast<XOutMessageList *>(obj);
}

XVariable * XModelTree::toXVariable(QObject *obj) {
  return static_cast<XVariable *>(obj);
}

XVariableList * XModelTree::toXVariableList(QObject *obj) {
  return static_cast<XVariableList *>(obj);
}

XFunction * XModelTree::toXFunction(QObject *obj) {
  return static_cast<XFunction *>(obj);
}

XFunctionList * XModelTree::toXFunctionList(QObject *obj) {
  return static_cast<XFunctionList *>(obj);
}

/////////////////////////////
// OPERATIONS BY NODE TYPE //
/////////////////////////////
QVariant XModelTree::dataForXModelWithRole(XModel *model, int role) const {
  if(role == Qt::DecorationRole){
	return QIcon(":/icons/xmme/images/im.png");
  }
  else if(role == Qt::FontRole){
    QFont font;
	if(!model->getEnabled()){
	  font.setItalic(true);
	}
    return QVariant(font);
  } 
  else if(role == Qt::ForegroundRole){
	if(!model->getEnabled()){
	  return QColor(Qt::gray);
	}
	return QColor(Qt::darkRed);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  } 

  return model->getName();
}

QVariant XModelTree::dataForXModelListWithRole(XModelList *modelList, int role) const {
  if(role == Qt::FontRole){
    QFont font;
	font.setItalic(true);
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }
  
  return "Nested Models";
}

QVariant XModelTree::dataForXEnvironmentWithRole(XEnvironment *environment, int role) const {
  if(role == Qt::FontRole){
    QFont font;
	font.setItalic(true);
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }
  
  return "Environment";
}

QVariant XModelTree::dataForXFileListWithRole(XFileList *fileList, int role) const {
  if(role == Qt::FontRole){
    QFont font;
	font.setItalic(true);
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }
  
  return "Function Files";
}

QVariant XModelTree::dataForXTimeUnitListWithRole(XTimeUnitList *timeUnitList, int role) const {
  if(role == Qt::FontRole){
    QFont font;
	font.setItalic(true);
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }
  
  return "Time Units";
}

QVariant XModelTree::dataForXTimeUnitWithRole(XTimeUnit *timeUnit, int role) const {
  if(role == Qt::DecorationRole){
	return QIcon(":/icons/xmme/images/document-open-recent.png");
  }
  else if(role == Qt::FontRole){
    QFont font;
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }
  
  return timeUnit->getName();
}

QVariant XModelTree::dataForXDataTypeListWithRole(XDataTypeList *dataTypeList, int role) const {
  if(role == Qt::FontRole){
    QFont font;
	font.setItalic(true);
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }
  
  return "Data Types";
}

QVariant XModelTree::dataForXDataTypeWithRole(XDataType *dataType, int role) const {
  if(role == Qt::DecorationRole){
	return QIcon(":/icons/xmme/images/insert-object.png");
  }
  else if(role == Qt::FontRole){
    QFont font;
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }
  
  return dataType->getName();
}
 
QVariant XModelTree::dataForXAgentWithRole(XAgent *agent, int role) const {
  if(role == Qt::DecorationRole){
	return QIcon(":/icons/xmme/images/emblem-people.png");
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }
  
  return agent->getName();
}

QVariant XModelTree::dataForXMessageWithRole(XMessage *message, int role) const {
  if(role == Qt::DecorationRole){
	return QIcon(":/icons/xmme/images/stock_mail.png");
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }
  
  return message->getName();
}

QVariant XModelTree::dataForXIOMessageWithRole(XIOMessage *IOMessage, int role) const {
  if(role != Qt::DisplayRole){
	return QVariant();
  }
  return IOMessage->msgPointer->getName();
}

QVariant XModelTree::dataForXAgentListWithRole(XAgentList *agentList, int role) const {
  if(role == Qt::FontRole){
    QFont font;
	font.setItalic(true);
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }

  return "Agents";
}

QVariant XModelTree::dataForXMessageListWithRole(XMessageList *messageList, int role) const {
  if(role == Qt::FontRole){
    QFont font;
	font.setItalic(true);
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }

  return "Messages";
}

QVariant XModelTree::dataForXInMessageListWithRole(XInMessageList *inMessageList, int role) const {
  if(role == Qt::FontRole){
    QFont font;
	font.setItalic(true);
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }

  return "Input";
}

QVariant XModelTree::dataForXOutMessageListWithRole(XOutMessageList *outMessageList, int role) const {
  if(role == Qt::FontRole){
    QFont font;
	font.setItalic(true);
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }

  return "Output";
}

QVariant XModelTree::dataForXVariableListWithRole(XVariableList *variableList, int role) const {
  if(role == Qt::FontRole){
    QFont font;
	font.setItalic(true);
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }

  if(this->isXMessage(variableList->getParent())){
	return "Variables";
  }
  else if(this->isXEnvironment(variableList->getParent())){
	return "Constants";
  }
  else if(this->isXDataType(variableList->getParent())){
	return "Attributes";
  }
  else{
	return "Memory";
  }
}

QVariant XModelTree::dataForXVariableWithRole(XVariable *variable, int role) const {
  if(role == Qt::DecorationRole){
	return QIcon(":/icons/xmme/images/stock_mail-druid-account.png");
  }
  else if(role == Qt::FontRole){
    QFont font;
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }

  return variable->getName();
}

QVariant XModelTree::dataForXFileWithRole(XFile *file, int role) const {
  if(role == Qt::DecorationRole){
	return QIcon(":/icons/xmme/images/functionFile.png");
  }
  else if(role == Qt::FontRole){
    QFont font;
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }

  return file->filePath;
}

QVariant XModelTree::dataForXFunctionListWithRole(XFunctionList *functionList, int role) const {
  if(role == Qt::FontRole){
    QFont font;
	font.setItalic(true);
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }
  
  return "Functions";
}

QVariant XModelTree::dataForXFunctionWithRole(XFunction *function, int role) const {
  if(role == Qt::DecorationRole){
	return QIcon(":/icons/xmme/images/function.png");
  }
  else if(role == Qt::FontRole){
    QFont font;
    return QVariant(font);
  }
  else if(role != Qt::DisplayRole){
	return QVariant();
  }

  return function->getName();
}

