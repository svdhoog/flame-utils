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
#include <XDataType.h>
#include <XDataTypeList.h>
#include <qtextstream.h>


// XModel::XModel() {
// 
// }

XDataType::XDataType(XDataTypeList * parent){
  this->parent = parent;
  this->variables = new XVariableList(this);
}

XDataType::XDataType(QDomDocument &dom, XDataTypeList * parent){

  this->parent = parent;
  
  QDomElement docElem = dom.documentElement();

  ///////////////////////////////////
  // SET MODEL'S PRIVATE DATATYPES //
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

XDataType::~XDataType() {

}

QString XDataType::getName() const {
  return this->name;
}

void XDataType::setName(const QString &name) {
  this->name = name;
}

QString XDataType::getDescription() const {
  return this->description;
}

void XDataType::setDescription(const QString &description) {
  this->description = description;
}

XDataTypeList * XDataType::getParent() const {
  return this->parent;
}

void XDataType::setParent(XDataTypeList *parent){
  this->parent = parent;
}

XVariableList * XDataType::getVariables() const {
  return this->variables;
}

void XDataType::setVariables(XVariableList *vars){
  this->variables = vars;
}

QString XDataType::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XAgen::toString()";
  return outString;
}

QString XDataType::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XDataType::toString(int depth)";
  return outString;
}

QString XDataType::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XDataType::toHTML()";
  return outString;
}

QDomDocument XDataType::toDomDocument() const {
  QDomDocument doc("XDataType");

  QDomElement root = doc.createElement("dataType");
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
