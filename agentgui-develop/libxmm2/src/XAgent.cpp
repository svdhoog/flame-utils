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
#include <XAgent.h>
#include <XAgentList.h>
#include <XVariableList.h>
#include <XFunctionList.h>
#include <qtextstream.h>
#include <qdebug.h>


// XModel::XModel() {
// 
// }

XAgent::XAgent(XAgentList * parent){
  this->parent = parent;
  this->variables = new XVariableList(this);
  this->functions = new XFunctionList(this);
}

XAgent::XAgent(QDomDocument &dom, XAgentList * parent){

  this->parent = parent;
  
  QDomElement docElem = dom.documentElement();

  ///////////////////////////////////
  // SET MODEL'S PRIVATE VARIABLES //
  ///////////////////////////////////

  QDomElement node = docElem.firstChildElement("name");

  if(!node.isNull()){
	this->setName(node.text());
  }

  node = docElem.firstChildElement("description");
  if(!node.isNull()){
	this->setDescription(node.text());
  }

  node = docElem.firstChildElement("memory");
  QDomDocument tmp("XVariables");
  tmp.appendChild(node.cloneNode());
  this->variables = new XVariableList(tmp, this);

  node = docElem.firstChildElement("functions");
  tmp = QDomDocument("XFunctions");
  tmp.appendChild(node.cloneNode());
  this->functions = new XFunctionList(tmp, this);
}

XAgent::~XAgent() {

}

XModel* XAgent::getTopLevelModel() const {
  if(this->getParent()){
	return this->getParent()->getTopLevelModel();
  }
  return NULL;
}

QString XAgent::getName() const {
  return this->name;
}

void XAgent::setName(const QString &name) {
  this->name = name;
}

QString XAgent::getDescription() const {
  return this->description;
}

void XAgent::setDescription(const QString &description) {
  this->description = description;
}

XAgentList * XAgent::getParent() const {
  return this->parent;
}

void XAgent::setParent(XAgentList *parent){
  this->parent = parent;
}

XVariableList * XAgent::getVariables() const {
  return this->variables;
}

void XAgent::setVariables(XVariableList *vars){
  this->variables = vars;
}

XFunctionList * XAgent::getFunctions() const {
  return this->functions;
}

void XAgent::setFunctions(XFunctionList *funcs){
  this->functions = funcs;
}

QString XAgent::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XAgen::toString()";
  return outString;
}

QString XAgent::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XAgent::toString(int depth)";
  return outString;
}

QString XAgent::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "<ul>";
  out << "<li>" << "<strong>Name:</strong> " << this->name << "</li>";
  out << "<li>" << "<strong>Description:</strong> " << this->description << "</li>";
  out << "<li>" << "<strong>Memory:</strong> " << this->variables->toHTML() << "</li>";
  out << "</ul>";
  return outString;
}

QDomDocument XAgent::toDomDocument() const {
  QDomDocument doc("XAgent");

  QDomElement root = doc.createElement("xagent");
  doc.appendChild(root);
  
  QDomElement name = doc.createElement("name");
  root.appendChild(name);
  QDomText nameT = doc.createTextNode(this->name);
  name.appendChild(nameT);
  
  QDomElement description = doc.createElement("description");
  root.appendChild(description);
  QDomText descriptionT = doc.createTextNode(this->description);
  description.appendChild(descriptionT);

  root.appendChild(this->getVariables()->toDomDocument("memory").documentElement());
  root.appendChild(this->getFunctions()->toDomDocument().documentElement());

  return doc;
}
