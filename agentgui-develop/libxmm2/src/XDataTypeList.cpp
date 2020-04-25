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

#include <qdebug.h>
#include <qdir.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qtextstream.h>

#include <XEnvironment.h>
#include <XMessage.h>
#include <XDataType.h>
#include <XDataTypeList.h>
#include <auxiliary.h>
#include <errors.h>

XDataTypeList::XDataTypeList(XEnvironment *parent) {
  this->parent = parent;
}

XDataTypeList::XDataTypeList(QDomDocument &dom, XEnvironment * parent){
  this->parent = parent;
  
  QDomElement docElem = dom.documentElement();

  /////////////////////////
  // SET NESTED MESSAGES //
  /////////////////////////

  QDomElement node = docElem;
  if(!node.isNull()){
	QDomNodeList nodeList = node.elementsByTagName("dataType");
	for(int i = 0; i < nodeList.size(); i++){
	  QDomDocument tmp("XDataType");
	  tmp.appendChild(nodeList.at(i).cloneNode());
	  this->dataTypeList << new XDataType(tmp, this);
	}
  }
}

XDataTypeList::~XDataTypeList() {

}

XEnvironment * XDataTypeList::getParent() const {
  return this->parent;
}

void XDataTypeList::setParent(XEnvironment *parent){
  this->parent = parent;
}

QString XDataTypeList::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XDataTypeList::toString()";
  return outString;
}

QString XDataTypeList::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XDataTypeList::toString(int depth)";
  return outString;
}

QString XDataTypeList::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "<ol>";
  for(int i = 0; i < this->dataTypeList.size(); i++){
	out << "<li>DataType Description" << this->dataTypeList.at(i)->toHTML() << "</li>";
  }
  out << "</ol>";
  return outString;
}

QDomDocument XDataTypeList::toDomDocument() const {
  QDomDocument doc("XDataTypeList");

  QDomElement root = doc.createElement("dataTypes");
  doc.appendChild(root);

  for(int i = 0; i < this->dataTypeList.size(); i++){
	root.appendChild(this->dataTypeList.at(i)->toDomDocument());
  }

  return doc;
}
