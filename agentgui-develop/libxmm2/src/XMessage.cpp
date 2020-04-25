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

#include <XModel.h>
#include <XMessage.h>
#include <XMessageList.h>
#include <qtextstream.h>


// XModel::XModel() {
// 
// }

XMessage::XMessage(XMessageList * parent){
  this->parent = parent;
  this->variables = new XVariableList(this);
}

XMessage::XMessage(QDomDocument &dom, XMessageList * parent){

  this->parent = parent;
  
  QDomElement docElem = dom.documentElement();

  ///////////////////////////////////
  // SET MODEL'S PRIVATE MESSAGES //
  ///////////////////////////////////

  QDomElement node = docElem.firstChildElement("name");

  if(!node.isNull()){
	this->setName(node.text());
  }

  node = docElem.firstChildElement("description");
  if(!node.isNull()){
	this->setDescription(node.text());
  }

  node = docElem.firstChildElement("variables");
  QDomDocument tmp("XVariables");
  tmp.appendChild(node.cloneNode());
  this->variables = new XVariableList(tmp, this);
}

XMessage::~XMessage() {

}

QString XMessage::getName() const {
  return this->name;
}

void XMessage::setName(const QString &name) {
  this->name = name;
}

QString XMessage::getDescription() const {
  return this->description;
}

void XMessage::setDescription(const QString &description) {
  this->description = description;
}

XMessageList * XMessage::getParent() const {
  return this->parent;
}

void XMessage::setParent(XMessageList *parent){
  this->parent = parent;
}

XVariableList * XMessage::getVariables() const {
  return this->variables;
}

void XMessage::setVariables(XVariableList *vars){
  this->variables = vars;
}

QString XMessage::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XAgen::toString()";
  return outString;
}

QString XMessage::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XMessage::toString(int depth)";
  return outString;
}

QString XMessage::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XMessage::toHTML()";
  return outString;
}

QDomDocument XMessage::toDomDocument() const {
  QDomDocument doc("XMessage");

  QDomElement root = doc.createElement("message");
  doc.appendChild(root);
  
  QDomElement name = doc.createElement("name");
  root.appendChild(name);
  QDomText nameT = doc.createTextNode(this->name);
  name.appendChild(nameT);
  
  QDomElement description = doc.createElement("description");
  root.appendChild(description);
  QDomText descriptionT = doc.createTextNode(this->description);
  description.appendChild(descriptionT);

  root.appendChild(this->getVariables()->toDomDocument("variables").documentElement());

  return doc;
}
