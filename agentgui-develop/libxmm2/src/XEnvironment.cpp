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
#include <XEnvironment.h>
#include <XVariable.h>
#include <XFileList.h>
#include <XTimeUnitList.h>
#include <XDataTypeList.h>

XEnvironment::XEnvironment(XModel * parent) {
  this->parent = parent;

  this->constants = new XVariableList(this);
  this->dataTypes = new XDataTypeList(this);  
  this->functionFiles = new XFileList(this);
  this->timeUnits = new XTimeUnitList(this);
}

XEnvironment::~XEnvironment() {

}

XEnvironment::XEnvironment(QDomDocument &dom, XModel * parent) {
  this->parent = parent;
  
  QDomElement docElem = dom.documentElement();

  QDomElement node = docElem.firstChildElement("constants");
  QDomDocument tmp("XConstants");
  tmp.appendChild(node.cloneNode());
  this->constants = new XVariableList(tmp, this);

  node = docElem.firstChildElement("functionFiles");
  tmp = QDomDocument("XConstants");
  tmp.appendChild(node.cloneNode());
  this->functionFiles = new XFileList(tmp, this);

  node = docElem.firstChildElement("timeUnits");
  tmp = QDomDocument("XTimeUnits");
  tmp.appendChild(node.cloneNode());
  this->timeUnits = new XTimeUnitList(tmp, this);
  
  node = docElem.firstChildElement("dataTypes");
  tmp = QDomDocument("XDataTypes");
  tmp.appendChild(node.cloneNode());
  this->dataTypes = new XDataTypeList(tmp, this);  
}

XModel* XEnvironment::getTopLevelModel() const {
  if(this->getParent()){
	return this->getParent()->getTopLevelModel();
  }
  return NULL;
}

XModel * XEnvironment::getParent() const {
  return this->parent;
}

void XEnvironment::setParent(XModel *parent){
  this->parent = parent;
}


XVariableList * XEnvironment::getConstants() {
  return this->constants;
}

void XEnvironment::setConstants(XVariableList *constants){
  this->constants = constants;
}

XFileList * XEnvironment::getFunctionFiles(){
  return this->functionFiles;
}

XTimeUnitList * XEnvironment::getTimeUnitList(){
  return this->timeUnits;
}

XDataTypeList * XEnvironment::getDataTypes(){
  return this->dataTypes;
}

QString XEnvironment::toString() const {
  return this->toString(0);
}

QString XEnvironment::toString(int depth = 0) const {
  QString outString;
  QTextStream out(&outString);
  QString tmp, app;
  if(depth == 0){
	tmp = "";
	app = "-";
  }
  else {
	tmp = "|";
	app = "";
  }

  QString parentName;
  if(this->parent){
	parentName = this->parent->getName() + " (" + this->parent->getVersion() + ")";
  }
  else{
	parentName = "";
  }

  out << tmp << QString(depth, ' ') << "," + QString(72 - depth, '-') + app<< endl;
  out << tmp << QString(depth, ' ') << "| Environment  : " << endl;
  out << tmp << QString(depth, ' ') << "| ==========  : "  << endl;
  out << tmp << QString(depth, ' ') << "| Prnt  : " << parentName << endl;
  out << tmp << QString(depth, ' ') << "| Constants" << endl;
  out << tmp << QString(depth, ' ') << "| =============" << endl;
  out << tmp << QString(depth, ' ') << "| Function Files" << endl;
  out << tmp << QString(depth, ' ') << "| =============" << endl;
  out << tmp << QString(depth, ' ') << "| Time Units" << endl;
  out << tmp << QString(depth, ' ') << "| =============" << endl;
  out << tmp << QString(depth, ' ') << "| Data Types" << endl;
  out << tmp << QString(depth, ' ') << "| =============" << endl;
//   for(int i = 0; i < this->models.size(); i++) {
// 	out << this->models.at(i)->toString(depth+1) << endl;
//   }
//   if(this->models.size() == 0){
// 	out << tmp << QString(depth, ' ') << "| (no nested models)" << endl;	
//   }
  out << tmp << QString(depth, ' ') << "`" + QString(72 - depth, '-') + app;
  return outString;
}

QString XEnvironment::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO";
  return outString;
}

QDomDocument XEnvironment::toDomDocument() const {
  QDomDocument doc("XEnvironment");

  QDomElement root = doc.createElement("environment");
  doc.appendChild(root);
  
  root.appendChild(this->constants->toDomDocument("constants").documentElement());
  root.appendChild(this->functionFiles->toDomDocument().documentElement());
  root.appendChild(this->timeUnits->toDomDocument().documentElement());
  root.appendChild(this->dataTypes->toDomDocument().documentElement());

  return doc;
}

