////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2008 Vehbi Sinan Tunalioglu <vst@vsthost.com>           //
//                                                                        //
//  This file is part of libxmm2.                                         //
//                                                                        //
//  libxmm2 is free software: you can redistribute it and/or              //
//  modify it under the terms of the GNU General Public License           //
//  as published by the Free Software Foundation, either version 3        //
//  of the License, or (at your option) any later version.                //
//                                                                        //
//  libxmm2 is distributed in the hope that it will be useful, but        //
//  WITHOUT ANY WARRANTY; without even the implied warranty of            //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     //
//  General Public License for more details.                              //
//                                                                        //
//  You should have received a copy of the GNU General Public License     //
//  along with libxmm2.  If not, see <http://www.gnu.org/licenses/>.      //
////////////////////////////////////////////////////////////////////////////

#include <qtextstream.h>
#include <qfile.h>
#include <qdir.h>
#include <qdebug.h>
#include <qfileinfo.h>
#include <XMessageList.h>
#include <XModel.h>
#include <XEnvironment.h>
#include <XModelList.h>
#include <XAgentList.h>
#include <XAgent.h>
#include <XMessage.h>
#include <errors.h>
#include <auxiliary.h>

XModel::XModel(XModelList * parent){
  this->parent = parent;
  this->enabled = true;

  this->agents = new XAgentList(this);
  this->environment = new XEnvironment(this);
  this->messages = new XMessageList(this);
  this->nestedModels = new XModelList(this);
}

XModel::XModel(const QString &modelXMLFilePath, XModelList * parent){
  this->parent = parent;
  this->enabled = true;
  this->pendingMsgInits.clear();

  this->filePath = modelXMLFilePath;

  QDomDocument doc("xmodel");

  QFile file(modelXMLFilePath);
  if (!file.open(QIODevice::ReadOnly)){
	throw new XError(XError::ModelFileNotOpened);
  }

  if(!doc.setContent(&file)){
	throw new XError(XError::ModelFileNotParsed);
  }

  QDomElement docElem = doc.documentElement();

  ///////////////////////////////////
  // SET MODEL'S PRIVATE VARIABLES //
  ///////////////////////////////////

  QDomElement node = docElem.firstChildElement("name");

  if(!node.isNull()){
	this->setName(node.text());
  }

  node = docElem.firstChildElement("version");

  if(!node.isNull()){
	this->setVersion(node.text());
  }

  node = docElem.firstChildElement("description");
  if(!node.isNull()){
	this->setDescription(node.text());
  }

  /////////////////////////
  // SET THE ENVIRONMENT //
  /////////////////////////

  node = docElem.firstChildElement("environment");
  QDomDocument tmp("XEnvironment");
  tmp.appendChild(node.cloneNode());
  this->environment = new XEnvironment(tmp, this);

  //////////////////////
  // SET THE MESSAGES //
  //////////////////////

  node = docElem.firstChildElement("messages");
  tmp = QDomDocument("XMessageList");
  tmp.appendChild(node.cloneNode());
  this->messages = new XMessageList(tmp, this);

  ///////////////////////
  // SET NESTED MODELS //
  ///////////////////////

  node = docElem.firstChildElement("models");
  tmp = QDomDocument("XModels");
  tmp.appendChild(node.cloneNode());
  this->nestedModels = new XModelList(tmp, this);
  this->nestedModels->init(tmp);

  /////////////////////
  // SET THE AGENTS  //
  /////////////////////

  node = docElem.firstChildElement("agents");
  tmp = QDomDocument("XAgents");
  tmp.appendChild(node.cloneNode());
  this->agents = new XAgentList(tmp, this);

  ////////////////////////////////////
  // GO OVER THE PENDING OPERATIONS //
  ////////////////////////////////////

  for(int i = 0; i < this->pendingMsgInits.size(); i++){
	//qDebug() << "Pending: " << this->pendingMsgInits.at(i)->messageName;
	//qDebug() << "   Here: " << this->getMessageByName(this->pendingMsgInits.at(i)->messageName);
	XMessage *pendingMsg = this->getMessageByName(this->pendingMsgInits.at(i)->messageName);
	if(pendingMsg){
	  this->pendingMsgInits.at(i)->msgPointer = pendingMsg;
	}
	else{
	  qDebug() << "Message has not been found:" << this->pendingMsgInits.at(i)->messageName;
	}
  }

}

XModel::~XModel() {

}

XModel* XModel::getTopLevelModel() {
  if(this->getParent()){
	return this->getParent()->getTopLevelModel();
  }
  return this;
}

QString XModel::getName() const {
  return this->name;
}

void XModel::setName(const QString &name) {
  this->name = name;
}

bool XModel::getEnabled() const{
  return this->enabled;
}

void XModel::setEnabled(bool enabled){
  this->enabled = enabled;
}

QString XModel::getVersion() const {
  return this->version;
}

void XModel::setVersion(const QString &version) {
  this->version = version;
}

QString XModel::getDescription() const {
  return this->description;
}

void XModel::setDescription(const QString &description) {
  this->description = description;
}

QString XModel::getFilePath() const {
  return this->filePath;
}

void XModel::setFilePath(const QString &filePath) {
  this->filePath = filePath;
}

int XModel::nestedModelCount() {
  return this->nestedModels->modelList.size();
}

XModel * XModel::getModelAt(int index) {
  if(!(index < this->nestedModelCount())){
	return NULL;
  }
  return this->getNestedModels()->modelList.at(index);
}

XModelList * XModel::getNestedModels() const {
  return this->nestedModels;
}

void XModel::setNestedModels(XModelList *modelList){
  this->nestedModels = modelList;
}

XAgentList * XModel::getAgents() const {
  return this->agents;
}

void XModel::setAgents(XAgentList *agents){
  this->agents = agents;
}

XMessage * XModel::getMessageByName(QString name) {
  XMessage * retVal = this->getMessages()->getMessageByName(name);
  if(retVal){
	return retVal;
  }
  for(int i = 0; i < this->nestedModels->modelList.size(); i++){
	retVal = this->getModelAt(i)->getMessageByName(name);
	if(retVal){
	  return retVal;
	}
  }
  return NULL;
}

XMessageList * XModel::getMessages() const {
  return this->messages;
}

QList<XMessage *> XModel::getAllMessages() {
  QList<XMessage *> ret;
  ret += this->messages->messageList;
  for(int i = 0; i < this->nestedModels->modelList.size(); i++){
	ret += this->getModelAt(i)->getAllMessages();
  }
  return ret;
}

void XModel::setMessages(XMessageList *messages){
  this->messages = messages;
}

XModel * XModel::getParentModel() const {
  if(this->parent && this->parent->getParent()){
	return this->parent->getParent();
  }
  return NULL;
}

XModelList * XModel::getParent() const {
  return this->parent;
}

void XModel::setParent(XModelList *parent){
  this->parent = parent;
}

XEnvironment * XModel::getEnvironment() {
  return this->environment;
}

void XModel::setEnvironment(XEnvironment *env){
  this->environment = env;
}

QString XModel::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XModelList::toString()";
  return outString;
}

QString XModel::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XModelList::toString(int depth)";
  return outString;
}

QString XModel::toHTML() const {
  QString outString;
  QTextStream out(&outString);

  out << "<ul>";
  out << "<li>" << "<strong>Name:</strong> " << this->name << "</li>";
  out << "<li>" << "<strong>Version:</strong> " << this->version << "</li>";
  out << "<li>" << "<strong>Description:</strong> " << this->description << "</li>";
  out << "</ul>";

  return outString;
}

QDomDocument XModel::toDomDocument() const {
  QDomDocument doc;

  QDomElement root = doc.createElement("xmodel");
  doc.appendChild(root);

  QDomAttr attVersion =  doc.createAttribute("version");
  attVersion.setValue("2");
  root.setAttributeNode(attVersion);

  QDomElement name = doc.createElement("name");
  root.appendChild(name);
  QDomText nameT = doc.createTextNode(this->name);
  name.appendChild(nameT);

  QDomElement version = doc.createElement("version");
  root.appendChild(version);
  QDomText versionT = doc.createTextNode(this->version);
  version.appendChild(versionT);

  QDomElement description = doc.createElement("description");
  root.appendChild(description);
  QDomText descriptionT = doc.createTextNode(this->description);
  description.appendChild(descriptionT);

  root.appendChild(this->nestedModels->toDomDocument().documentElement());
  root.appendChild(this->environment->toDomDocument().documentElement());
  root.appendChild(this->agents->toDomDocument().documentElement());
  root.appendChild(this->messages->toDomDocument().documentElement());

  return doc;
}

QDir XModel::getFileDir() const{
  QDir tmp(this->getFilePath());
  tmp.cdUp();
  return tmp;
}

bool XModel::save(){
  QFile file(this->getFilePath());

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
	QDir tmpDir(QFileInfo(file).absolutePath());
	if(!tmpDir.exists()){
	  if(!tmpDir.mkpath(QFileInfo(file).absolutePath())){
		return false;
	  }
	  else{
		if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
		  return false;
		}
	  }
	}
	else{
	  return false;
	}
  }

  QTextStream out(&file);

  out << this->toDomDocument().toString();
  file.close();

  for(int i = 0; i < this->nestedModelCount(); i++){
	this->nestedModels->modelList.at(i)->save();
  }

  return true;
}
