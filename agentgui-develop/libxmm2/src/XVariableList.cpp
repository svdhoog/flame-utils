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
#include <XVariableList.h>
#include <XVariable.h>
#include <XMessage.h>
#include <errors.h>
#include <auxiliary.h>

XVariableList::XVariableList(QObject *parent) {
  this->parent = parent;
}

XVariableList::XVariableList(QDomDocument &dom, QObject * parent){

  this->parent = parent;
  
  QDomElement docElem = dom.documentElement();

  /////////////////////////
  // SET NESTED MESSAGES //
  /////////////////////////

  QDomElement node = docElem;
  if(!node.isNull()){
	QDomNodeList nodeList = node.elementsByTagName("variable");
	for(int i = 0; i < nodeList.size(); i++){
	  QDomDocument tmp("XVariable");
	  tmp.appendChild(nodeList.at(i).cloneNode());
	  this->variableList << new XVariable(tmp, this);
	}
  }
}

XVariableList::~XVariableList() {

}

QObject * XVariableList::getParent() const {
  return this->parent;
}

void XVariableList::setParent(QObject *parent){
  this->parent = parent;
}

QString XVariableList::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XVariableList::toString()";
  return outString;
}

QString XVariableList::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XVariableList::toString(int depth)";
  return outString;
}

QString XVariableList::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "<ol>";
  for(int i = 0; i < this->variableList.size(); i++){
	out << "<li>Variable Description" << this->variableList.at(i)->toHTML() << "</li>";
  }
  out << "</ol>";
  return outString;
}

QDomDocument XVariableList::toDomDocument(const QString &wrapperTag) const {
  QDomDocument doc("XVariableList");

  QDomElement root = doc.createElement(wrapperTag);
  doc.appendChild(root);

  for(int i = 0; i < this->variableList.size(); i++){
	root.appendChild(this->variableList.at(i)->toDomDocument());
  }

  return doc;
}

