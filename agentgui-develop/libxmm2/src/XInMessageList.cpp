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
#include <XInMessageList.h>
#include <XMessage.h>
#include <XIOMessage.h>
#include <XModel.h>
#include <errors.h>
#include <auxiliary.h>
#include <XFunction.h>

XInMessageList::XInMessageList(XFunction * parent){
  this->parent = parent;
}

XInMessageList::~XInMessageList() {

}

XModel* XInMessageList::getTopLevelModel() const{
  if(this->parent){
	return this->parent->getTopLevelModel();
  }
  return NULL;
}

XFunction* XInMessageList::getParent() const {
  return this->parent;
}

void XInMessageList::setParent(XFunction *parent){
  this->parent = parent;
}

XMessage * XInMessageList::getMessageByName(QString name){
  for(int i = 0; i < this->messageList.size(); i++){
	if(this->messageList.at(i)->msgPointer->getName() == name){
	  return this->messageList.at(i)->msgPointer;
	}
  }
  return NULL;
}

QString XInMessageList::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XInMessageList::toString()";
  return outString;
}

QString XInMessageList::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XInMessageList::toString(int depth)";
  return outString;
}

QString XInMessageList::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XInMessageList::toHTML()";
  return outString;
}

QDomDocument XInMessageList::toDomDocument() const {
  QDomDocument doc("XMessageOut");

  QDomElement root = doc.createElement("inputs");
  doc.appendChild(root);

  for(int i = 0; i < this->messageList.size(); i++){
	QDomElement tmpO = doc.createElement("input");
	root.appendChild(tmpO);

	QDomElement tmpMsgName = doc.createElement("messageName");
	tmpO.appendChild(tmpMsgName);

	QDomText msgName = doc.createTextNode(this->messageList.at(i)->msgPointer->getName());
	tmpMsgName.appendChild(msgName);

	QDomDocument tmpdoc("");
	tmpdoc.setContent(this->messageList.at(i)->filter, false);
	QDomElement tmpFilter = tmpdoc.documentElement();
	tmpO.appendChild(tmpFilter);  
  }

  return doc;
}
