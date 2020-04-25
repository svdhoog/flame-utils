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
#include <XTimeUnit.h>
#include <XTimeUnitList.h>
#include <auxiliary.h>
#include <errors.h>

XTimeUnitList::XTimeUnitList(XEnvironment * parent) {
  this->parent = parent;
}

XTimeUnitList::XTimeUnitList(QDomDocument &dom, XEnvironment * parent) {

  this->parent = parent;
  
  QDomElement docElem = dom.documentElement();

  /////////////////////////
  // SET NESTED MESSAGES //
  /////////////////////////

  QDomElement node = docElem;
  if(!node.isNull()){
	QDomNodeList nodeList = node.elementsByTagName("timeUnit");
	for(int i = 0; i < nodeList.size(); i++){
	  QDomDocument tmp("XTimeUnit");
	  tmp.appendChild(nodeList.at(i).cloneNode());
	  this->timeUnitList << new XTimeUnit(tmp, this);
	}
  }
}

XTimeUnitList::~XTimeUnitList() {

}

XEnvironment * XTimeUnitList::getParent() const {
  return this->parent;
}

void XTimeUnitList::setParent(XEnvironment *parent){
  this->parent = parent;
}

QString XTimeUnitList::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XTimeUnitList::toString()";
  return outString;
}

QString XTimeUnitList::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XTimeUnitList::toString(int depth)";
  return outString;
}

QString XTimeUnitList::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "<ol>";
  for(int i = 0; i < this->timeUnitList.size(); i++){
	out << "<li>TimeUnit Description" << this->timeUnitList.at(i)->toHTML() << "</li>";
  }
  out << "</ol>";
  return outString;
}

QDomDocument XTimeUnitList::toDomDocument() const {
  QDomDocument doc("XTimeUnitList");

  QDomElement root = doc.createElement("timeUnits");
  doc.appendChild(root);

  for(int i = 0; i < this->timeUnitList.size(); i++){
	root.appendChild(this->timeUnitList.at(i)->toDomDocument());
  }

  return doc;
}
