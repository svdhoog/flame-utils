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
#include <XOutMessageList.h>
#include <XMessage.h>
#include <XFunction.h>
#include <XIOMessage.h>
#include <XModel.h>
#include <errors.h>
#include <auxiliary.h>

XOutMessageList::XOutMessageList(XFunction * parent){
  this->parent = parent;
}

XOutMessageList::~XOutMessageList() {

}

XFunction * XOutMessageList::getParent() const {
  return this->parent;
}

XModel* XOutMessageList::getTopLevelModel() const{
  if(this->parent){
	return this->parent->getTopLevelModel();
  }
  return NULL;
}

void XOutMessageList::setParent(XFunction *parent){
  this->parent = parent;
}

XMessage * XOutMessageList::getMessageByName(QString name){
  for(int i = 0; i < this->messageList.size(); i++){
	if(this->messageList.at(i)->msgPointer->getName() == name){
	  return this->messageList.at(i)->msgPointer;
	}
  }
  return NULL;
}

QString XOutMessageList::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XOutMessageList::toString()";
  return outString;
}

QString XOutMessageList::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XOutMessageList::toString(int depth)";
  return outString;
}

QString XOutMessageList::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XOutMessageList::toHTML()";
  return outString;
}

QDomDocument XOutMessageList::toDomDocument() const {
  QDomDocument doc("XMessageOut");

  QDomElement root = doc.createElement("outputs");
  doc.appendChild(root);

  for(int i = 0; i < this->messageList.size(); i++){
	QDomElement tmpO = doc.createElement("output");
	root.appendChild(tmpO);

	QDomElement tmpMsgName = doc.createElement("messageName");
	tmpO.appendChild(tmpMsgName);

	QDomText msgName = doc.createTextNode(this->messageList.at(i)->msgPointer->getName());
	tmpMsgName.appendChild(msgName);
  }

  return doc;
}
