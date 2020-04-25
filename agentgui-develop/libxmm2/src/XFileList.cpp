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
#include <XFileList.h>
#include <XEnvironment.h>
#include <XFile.h>
#include <XModel.h>
#include <errors.h>
#include <auxiliary.h>

XFileList::XFileList(XEnvironment * parent) {
  this->parent = parent;
}

XFileList::XFileList(QDomDocument &dom, XEnvironment * parent){
  this->parent = parent;

  QDomElement docElem = dom.documentElement();
  QDomElement node = docElem;
  if(!node.isNull()){
	QDomNodeList nodeList = node.elementsByTagName("file");
	for(int i = 0; i < nodeList.size(); i++){
	  this->fileList << new XFile(nodeList.at(i).toElement().text(), this);
	}
  }
}

XFileList::~XFileList() {

}

XModel* XFileList::getTopLevelModel() const {
  if(this->getParent()){
	return this->getParent()->getTopLevelModel();
  }
  return NULL;
}

XEnvironment * XFileList::getParent() const {
  return this->parent;
}

void XFileList::setParent(XEnvironment *parent){
  this->parent = parent;
}

QString XFileList::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XFileList::toString()";
  return outString;
}

QString XFileList::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XFileList::toString(int depth)";
  return outString;
}

QString XFileList::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XFileList::toHTML()";
  return outString;
}

QDomDocument XFileList::toDomDocument() const {
  QDomDocument doc("XFileList");

  QDomElement root = doc.createElement("functionFiles");
  doc.appendChild(root);

  for(int i = 0; i < this->fileList.size(); i++){
	root.appendChild(this->fileList.at(i)->toDomDocument());
  }

  return doc;  
}
