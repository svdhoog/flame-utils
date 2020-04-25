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
#include <XAgentList.h>
#include <XAgent.h>
#include <XModel.h>
#include <errors.h>
#include <auxiliary.h>

XAgentList::XAgentList(XModel * parent){
  this->parent = parent;
}

XAgentList::XAgentList(QDomDocument &dom, XModel * parent){

  this->parent = parent;
  
  QDomElement docElem = dom.documentElement();

  ///////////////////////
  // SET NESTED MODELS //
  ///////////////////////

  QDomElement node = docElem;
  if(!node.isNull()){
	QDomNodeList nodeList = node.elementsByTagName("xagent");
	for(int i = 0; i < nodeList.size(); i++){
	  QDomDocument tmp("XAgent");
	  tmp.appendChild(nodeList.item(i).cloneNode());
	  this->agentList << new XAgent(tmp, this);
	}
  }
}

XAgentList::~XAgentList() {

}

XModel* XAgentList::getTopLevelModel() const {
  if(this->getParent()){
	return this->getParent()->getTopLevelModel();
  }
  return NULL;
}

XModel * XAgentList::getParent() const {
  return this->parent;
}

void XAgentList::setParent(XModel *parent){
  this->parent = parent;
}

QString XAgentList::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XAgentList::toString()";
  return outString;
}

QString XAgentList::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XAgentList::toString(int depth)";
  return outString;
}

QString XAgentList::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "<h1>" << "Agent List" << "</h1>";
  out << "<ol>";
  for(int i = 0; i < this->agentList.size(); i++){
	out << "<li>Agent Description" << this->agentList.at(i)->toHTML() << "</li>";
  }
  out << "</ol>";
  return outString;
}

QDomDocument XAgentList::toDomDocument() const {
  QDomDocument doc("XAgentList");

  QDomElement root = doc.createElement("agents");
  doc.appendChild(root);
  
  for(int i = 0; i < this->agentList.size(); i++){
	root.appendChild(this->agentList.at(i)->toDomDocument());
  }

  return doc;
}
