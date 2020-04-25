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
#include <XModelList.h>
#include <XModel.h>
#include <errors.h>
#include <auxiliary.h>

XModelList::XModelList(XModel * parent){
  this->parent = parent;
}

XModelList::XModelList(QDomDocument &dom, XModel * parent){
  this->parent = parent;
}

void XModelList::init(QDomDocument &dom){
  QDomElement docElem = dom.documentElement();

  ///////////////////////
  // SET NESTED MODELS //
  ///////////////////////

  QDomElement node = docElem;//.firstChildElement("models");
  if(!node.isNull()){
	QDomNodeList nodeList = node.elementsByTagName("model");
	for(int i = 0; i < nodeList.size(); i++){
	  QString nestedModelFile = nodeList.at(i).firstChildElement("file").text();
	  bool isEnabled = (nodeList.at(i).firstChildElement("enabled").text() == "true");
	  QFileInfo finfo(this->parent->getFilePath());
	  try {
		XModel *tmp = new XModel(finfo.absoluteDir().absolutePath() + "/" + nestedModelFile, this);
		tmp->setEnabled(isEnabled);
		this->modelList << tmp;
	  }
	  catch (...) {
		//qDebug() << "Problem while reading one of the XModel files:" << finfo.absoluteDir().absolutePath() + "/" + nestedModelFile;
	  }
	}
  }
}

XModelList::~XModelList() {

}

XModel* XModelList::getTopLevelModel() const {
  if(this->getParent()){
	return this->getParent()->getTopLevelModel();
  }
  return NULL;
}

XModel * XModelList::getParent() const {
  return this->parent;
}

void XModelList::setParent(XModel *parent){
  this->parent = parent;
}

QString XModelList::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XModelList::toString()";
  return outString;
}

QString XModelList::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XModelList::toString(int depth)";
  return outString;
}

QString XModelList::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "<h1>" << "Nested Model List" << "</h1>";
  out << "<ol>";
  for(int i = 0; i < this->modelList.size(); i++){
	out << "<li>Model Description" << this->modelList.at(i)->toHTML() << "</li>";
  }
  out << "</ol>";
  return outString;
}

QDomDocument XModelList::toDomDocument() const {
  QDomDocument doc("XModelList");

  QDomElement root = doc.createElement("models");
  doc.appendChild(root);

  for(int i = 0; i < this->modelList.size(); i++){

	QDomElement model = doc.createElement("model");

	QDomElement file = doc.createElement("file");
	model.appendChild(file);
	QDomText path = doc.createTextNode(this->getTopLevelModel()->getFileDir().relativeFilePath(this->modelList.at(i)->getFilePath()));
	file.appendChild(path);

	QDomElement enabled = doc.createElement("enabled");
	model.appendChild(enabled);
	QDomText isEnabled;
	if(this->modelList.at(i)->getEnabled()){
	  isEnabled = doc.createTextNode("true");
	}
	else{
	  isEnabled = doc.createTextNode("false");
	}
	enabled.appendChild(isEnabled);

	root.appendChild(model);
  }

  return doc;
}
