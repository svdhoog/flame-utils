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
#include <XVariable.h>
#include <XVariableList.h>
#include <qtextstream.h>


// XModel::XModel() {
// 
// }

XVariable::XVariable(XVariableList * parent){
  this->parent = parent;
}

XVariable::XVariable(QDomDocument &dom, XVariableList * parent){

  this->parent = parent;
  
  QDomElement docElem = dom.documentElement();

  ///////////////////////////////////
  // SET MODEL'S PRIVATE VARIABLES //
  ///////////////////////////////////

  QDomElement node = docElem.firstChildElement("type");

  if(!node.isNull()){
	this->setType(node.text());
  }

  node = docElem.firstChildElement("name");

  if(!node.isNull()){
	this->setName(node.text());
  }

  node = docElem.firstChildElement("description");
  if(!node.isNull()){
	this->setDescription(node.text());
  }
}

XVariable::~XVariable() {

}

QString XVariable::getType() const {
  return this->type;
}

void XVariable::setType(const QString &type) {
  this->type = type;
}

QString XVariable::getName() const {
  return this->name;
}

void XVariable::setName(const QString &name) {
  this->name = name;
}

QString XVariable::getDescription() const {
  return this->description;
}

void XVariable::setDescription(const QString &description) {
  this->description = description;
}

XVariableList * XVariable::getParent() const {
  return this->parent;
}

void XVariable::setParent(XVariableList *parent){
  this->parent = parent;
}

QString XVariable::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XVariable::toString()";
  return outString;
}

QString XVariable::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XVariable::toString(int depth)";
  return outString;
}

QString XVariable::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "<ul>";
  out << "<li>" << "<strong>Type:</strong> " << this->type << "</li>";
  out << "<li>" << "<strong>Name:</strong> " << this->name << "</li>";
  out << "<li>" << "<strong>Description:</strong> " << this->description << "</li>";
  out << "</ul>";
  return outString;
}


QDomDocument XVariable::toDomDocument() const {
  QDomDocument doc("XVariable");

  QDomElement root = doc.createElement("variable");
  doc.appendChild(root);
  
  QDomElement type = doc.createElement("type");
  root.appendChild(type);
  QDomText typeT = doc.createTextNode(this->type);
  type.appendChild(typeT);
  
  QDomElement name = doc.createElement("name");
  root.appendChild(name);
  QDomText nameT = doc.createTextNode(this->name);
  name.appendChild(nameT);
  
  QDomElement description = doc.createElement("description");
  root.appendChild(description);
  QDomText descriptionT = doc.createTextNode(this->description);
  description.appendChild(descriptionT);

  return doc;
}
