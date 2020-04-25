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
#include <qdebug.h>
#include <XModel.h>
#include "XFunction.h"
#include "XFunctionList.h"
#include "XMessage.h"
#include "XAgent.h"
#include "XAgentList.h"
#include "XIOMessage.h"
#include "XOutMessageList.h"
#include "XInMessageList.h"

// XFunction::XFunction() {

// }

XFunction::XFunction(XFunctionList * parent) {
  this->parent = parent;
  this->messagesIn = new XInMessageList(this);
  this->messagesOut = new XOutMessageList(this);
}

XFunction::XFunction(QDomDocument &dom, XFunctionList * parent) {

  this->parent = parent;
  
  QDomElement varNode = dom.documentElement();

  if(!varNode.isNull()){
	this->name = varNode.firstChildElement("name").text();
	this->description = varNode.firstChildElement("description").text();
	this->code = varNode.firstChildElement("code").text();
	this->currentState = varNode.firstChildElement("currentState").text();
	this->nextState = varNode.firstChildElement("nextState").text();
	QDomDocument doc("");
	QDomElement root = doc.createElement("MyML");
	doc.appendChild(varNode.firstChildElement("condition"));
	this->condition = doc.toString();

	XModel *topMostLevelModel = this->getTopLevelModel();
	QDomElement inputs = varNode.firstChildElement("inputs");

	this->messagesIn = new XInMessageList(this);
	if(!inputs.isNull()){
	  QDomNodeList nodeList = inputs.elementsByTagName("input");
	  for(int i = 0; i < nodeList.size(); i++){
		QString messageName = nodeList.at(i).firstChildElement("messageName").text();
		QDomElement filterElement = nodeList.at(i).firstChildElement("filter");
		QString filter;
		if(!filterElement.isNull()){
		  QDomDocument doc2("");
		  QDomElement root2 = doc2.createElement("MyML");
		  doc2.appendChild(filterElement);
		  filter = doc2.toString();
		}
		else{
		  filter = "";
		}
		//XModel *topLevelModel = this->getTopLevelModel();
		XModel *topLevelModel = this->getParentModel();
		bool found = false;
		while(topLevelModel){
		  XMessage *tmpMesg = topLevelModel->getMessageByName(messageName);
		  if(tmpMesg){
			// The message is already defined and initialized. We can
			// proceed normally.
			XIOMessage * tmpIOMessage = new XIOMessage(tmpMesg, this->messagesIn);
			tmpIOMessage->filter = filter;
			tmpIOMessage->messageName = messageName;
			this->messagesIn->messageList << tmpIOMessage;
			qDebug() << "Message was initialized and used : " << messageName;
			found = true;
			break;
		  }
		  topLevelModel = topLevelModel->getParentModel();
		}
		if(!found){
		  // The message is not initialized yet. It is probably in
		  // one of the neighbour models which have not been
		  // initialized yet.
		  XIOMessage * tmpIOMessage = new XIOMessage(NULL, this->messagesIn);
		  tmpIOMessage->filter = filter;
		  tmpIOMessage->messageName = messageName;
		  this->messagesIn->messageList << tmpIOMessage;
		  qDebug() << "Message not initialized yet (IN) : " << messageName;
		  topMostLevelModel->pendingMsgInits << tmpIOMessage;
		}
	  }
	}

	QDomElement outputs = varNode.firstChildElement("outputs");

	this->messagesOut = new XOutMessageList(this);
	if(!outputs.isNull()){
	  QDomNodeList nodeList = outputs.elementsByTagName("output");
	  for(int i = 0; i < nodeList.size(); i++){
		QString messageName = nodeList.at(i).firstChildElement("messageName").text();
		XModel *topLevelModel = this->getParentModel();
		bool found = false;
		while(topLevelModel){
		  XMessage *tmpMesg = topLevelModel->getMessageByName(messageName);
		  if(tmpMesg){
			this->messagesOut->messageList << new XIOMessage(tmpMesg, this->messagesOut);
			found = true;
			break;
		  }
		  topLevelModel = topLevelModel->getParentModel();
		}
		if(!found){
		  // The message is not initialized yet. It is probably in
		  // one of the neighbour models which have not been
		  // initialized yet.
		  XIOMessage * tmpIOMessage = new XIOMessage(NULL, this->messagesIn);
		  tmpIOMessage->messageName = messageName;
		  this->messagesOut->messageList << tmpIOMessage;
		  qDebug() << "Message not initialized yet (OUT): " << messageName;
		  topMostLevelModel->pendingMsgInits << tmpIOMessage;
		}
	  }
	}
  }
}

XFunction::~XFunction() {

}

XModel* XFunction::getTopLevelModel() const {
  if(this->getParent()){
	return this->getParent()->getTopLevelModel();
  }
  return NULL;
}

XModel* XFunction::getParentModel() const {
  if(this->getParent() && this->getParent()->getParent() &&
	 ((XAgent*)this->getParent()->getParent())->getParent() &&
	 ((XAgent*)this->getParent()->getParent())->getParent()->getParent() ){
	return ((XAgent*)this->getParent()->getParent())->getParent()->getParent();
  }
  return NULL;
}

QString XFunction::getName() const {
  return this->name;
}

void XFunction::setName(const QString &name) {
  this->name = name;
}

QString XFunction::getCurrentState() const {
  return this->currentState;
}

void XFunction::setCurrentState(const QString &currentState) {
  this->currentState = currentState;
}

QString XFunction::getNextState() const {
  return this->nextState;
}

void XFunction::setNextState(const QString &nextState) {
  this->nextState = nextState;
}

QString XFunction::getDescription() const {
  return this->description;
}

void XFunction::setDescription(const QString &description) {
  this->description = description;
}

QString XFunction::getCondition() const {
  return this->condition;
}

void XFunction::setCondition(const QString &condition) {
  this->condition = condition;
}

QString XFunction::getCode() const {
  return this->code;
}

void XFunction::setCode(const QString &code) {
  this->code = code;
}

XFunctionList * XFunction::getParent() const {
  return this->parent;
}

void XFunction::setParent(XFunctionList *parent){
  this->parent = parent;
}

QString XFunction::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XAgen::toString()";
  return outString;
}

QString XFunction::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XFunction::toString(int depth)";
  return outString;
}

QString XFunction::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XFunction::toHTML()";
  return outString;
}

QDomDocument XFunction::toDomDocument() const {
  QDomDocument doc("XFunction");

  QDomElement root = doc.createElement("function");
  doc.appendChild(root);
  
  QDomElement name = doc.createElement("name");
  root.appendChild(name);
  QDomText nameT = doc.createTextNode(this->name);
  name.appendChild(nameT);
  
  QDomElement description = doc.createElement("description");
  root.appendChild(description);
  QDomText descriptionT = doc.createTextNode(this->description);
  description.appendChild(descriptionT);

  QDomElement currenState = doc.createElement("currentState");
  root.appendChild(currenState);
  QDomText currenStateT = doc.createTextNode(this->currentState);
  currenState.appendChild(currenStateT);

  QDomElement nextState = doc.createElement("nextState");
  root.appendChild(nextState);
  QDomText nextStateT = doc.createTextNode(this->nextState);
  nextState.appendChild(nextStateT);

  QDomDocument tmpdoc("");
  tmpdoc.setContent(this->condition, false);
  QDomElement condition = tmpdoc.documentElement();
  root.appendChild(condition);

  root.appendChild(this->messagesIn->toDomDocument().documentElement());
  root.appendChild(this->messagesOut->toDomDocument().documentElement());

  return doc;
}
