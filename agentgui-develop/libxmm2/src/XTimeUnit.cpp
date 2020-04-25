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
#include <XTimeUnit.h>
#include <XTimeUnitList.h>
#include <qtextstream.h>


// XModel::XModel() {
// 
// }

XTimeUnit::XTimeUnit(XTimeUnitList * parent){
  this->parent = parent;
}

XTimeUnit::XTimeUnit(QDomDocument &dom, XTimeUnitList * parent){

  this->parent = parent;
  
  QDomElement docElem = dom.documentElement();

  ///////////////////////////////////
  // SET MODEL'S PRIVATE TIMEUNITS //
  ///////////////////////////////////

  QDomElement node = docElem.firstChildElement("name");

  if(!node.isNull()){
	this->setName(node.text());
  }

  node = docElem.firstChildElement("unit");

  if(!node.isNull()){
	this->setUnit(node.text());
  }

  node = docElem.firstChildElement("period");
  if(!node.isNull()){
	this->setPeriod(node.text());
  }
}

XTimeUnit::~XTimeUnit() {

}

QString XTimeUnit::getName() const {
  return this->name;
}

void XTimeUnit::setName(const QString &name) {
  this->name = name;
}

QString XTimeUnit::getUnit() const {
  return this->unit;
}

void XTimeUnit::setUnit(const QString &unit) {
  this->unit = unit;
}

QString XTimeUnit::getPeriod() const {
  return this->period;
}

void XTimeUnit::setPeriod(const QString &period) {
  this->period = period;
}

XTimeUnitList * XTimeUnit::getParent() const {
  return this->parent;
}

void XTimeUnit::setParent(XTimeUnitList *parent){
  this->parent = parent;
}

QString XTimeUnit::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XTimeUnit::toString()";
  return outString;
}

QString XTimeUnit::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XTimeUnit::toString(int depth)";
  return outString;
}

QString XTimeUnit::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "<ul>";
  out << "<li>" << "<strong>Name:</strong> " << this->name << "</li>";
  out << "<li>" << "<strong>Unit:</strong> " << this->unit << "</li>";
  out << "<li>" << "<strong>Period:</strong> " << this->period << "</li>";
  out << "</ul>";
  return outString;
}


QDomDocument XTimeUnit::toDomDocument() const {
  QDomDocument doc("XTimeUnit");

  QDomElement root = doc.createElement("timeUnit");
  doc.appendChild(root);
  
  QDomElement name = doc.createElement("name");
  root.appendChild(name);
  QDomText nameT = doc.createTextNode(this->name);
  name.appendChild(nameT);
  
  QDomElement unit = doc.createElement("unit");
  root.appendChild(unit);
  QDomText unitT = doc.createTextNode(this->unit);
  unit.appendChild(unitT);
  
  QDomElement period = doc.createElement("period");
  root.appendChild(period);
  QDomText periodT = doc.createTextNode(this->period);
  period.appendChild(periodT);

  return doc;
}
