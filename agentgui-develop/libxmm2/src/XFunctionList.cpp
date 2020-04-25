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
#include <XM.h>
#include <XFunctionList.h>
#include <XFunction.h>
#include <XMessage.h>
#include <XAgent.h>
#include <errors.h>
#include <auxiliary.h>

XFunctionList::XFunctionList(QObject * parent){
  this->parent = parent;
}

XFunctionList::XFunctionList(QDomDocument &dom, QObject * parent){

  this->parent = parent;
  
  QDomElement docElem = dom.documentElement();

  /////////////////////////
  // SET NESTED MESSAGES //
  /////////////////////////

  QDomElement node = docElem;
  if(!node.isNull()){
	QDomNodeList nodeList = node.elementsByTagName("function");
	for(int i = 0; i < nodeList.size(); i++){
	  QDomDocument tmp("XFunction");
	  tmp.appendChild(nodeList.at(i).cloneNode());
	  this->functionList << new XFunction(tmp, this);
	}
  }
}

XFunctionList::~XFunctionList() {

}

XModel* XFunctionList::getTopLevelModel() const {
  if(this->getParent() && QString(this->getParent()->metaObject()->className()) == "XAgent"){
	return (static_cast<XAgent*>(this->getParent()))->getTopLevelModel();
  }
  return NULL;
}

QObject * XFunctionList::getParent() const {
  return this->parent;
}

void XFunctionList::setParent(QObject *parent){
  this->parent = parent;
}

QString XFunctionList::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XFunctionList::toString()";
  return outString;
}

QString XFunctionList::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XFunctionList::toString(int depth)";
  return outString;
}

QString XFunctionList::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XFunctionList::toHTML()";
  return outString;
}

QDomDocument XFunctionList::toDomDocument() const {
  QDomDocument doc("XFunctionList");

  QDomElement root = doc.createElement("functions");
  doc.appendChild(root);
  
  for(int i = 0; i < this->functionList.size(); i++){
	root.appendChild(this->functionList.at(i)->toDomDocument());
  }

  return doc;
}
