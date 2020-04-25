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
#include <XMessageList.h>
#include <XMessage.h>
#include <XModel.h>
#include <errors.h>
#include <auxiliary.h>

XMessageList::XMessageList(XModel * parent) {
  this->parent = parent;
}

XMessageList::XMessageList(QDomDocument &dom, XModel * parent){
  this->parent = parent;
  
  QDomElement docElem = dom.documentElement();

  /////////////////////////
  // SET NESTED MESSAGES //
  /////////////////////////

  QDomElement node = docElem;
  if(!node.isNull()){
	QDomNodeList nodeList = node.elementsByTagName("message");
	for(int i = 0; i < nodeList.size(); i++){
	  QDomDocument tmp("XMessage");
	  tmp.appendChild(nodeList.at(i).cloneNode());
	  this->messageList << new XMessage(tmp, this);
	}
  }

}

XMessageList::~XMessageList() {

}

XModel * XMessageList::getParent() const {
  return this->parent;
}

void XMessageList::setParent(XModel *parent){
  this->parent = parent;
}

XMessage * XMessageList::getMessageByName(QString name){
  for(int i = 0; i < this->messageList.size(); i++){
	if(this->messageList.at(i)->getName() == name){
	  return this->messageList.at(i);
	}
  }
  return NULL;
}

QString XMessageList::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XMessageList::toString()";
  return outString;
}

QString XMessageList::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XMessageList::toString(int depth)";
  return outString;
}

QString XMessageList::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XMessageList::toHTML()";
  return outString;
}

QDomDocument XMessageList::toDomDocument() const {
  QDomDocument doc("XVariableList");

  QDomElement root = doc.createElement("messages");
  doc.appendChild(root);

  for(int i = 0; i < this->messageList.size(); i++){
	root.appendChild(this->messageList.at(i)->toDomDocument());
  }

  return doc;
}
