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
#include <XFile.h>
#include <XFileList.h>
#include <qtextstream.h>
#include <qdebug.h>
#include <QDir>


// XModel::XModel() {
// 
// }

XFile::XFile(XFileList * parent){
  this->parent = parent;
}

XFile::XFile(QString filePath, XFileList * parent){
  this->parent = parent;
  this->filePath = filePath;
}

XFile::~XFile() {

}

void XFile::setFilePath(const QString& filePath){
  this->filePath = this->getParent()->getTopLevelModel()->getFileDir().relativeFilePath(filePath);
}

QString XFile::getFilePath() const{
  return this->filePath;
}

XFileList * XFile::getParent() const {
  return this->parent;
}

void XFile::setParent(XFileList *parent){
  this->parent = parent;
}

QString XFile::toString() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XFile::toString()";
  return outString;
}

QString XFile::toString(int depth) const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XFile::toString(int depth)";
  return outString;
}

QString XFile::toHTML() const {
  QString outString;
  QTextStream out(&outString);
  out << "TODO: in XFile::toHTML()";
  return outString;
}


QDomDocument XFile::toDomDocument() const {
  QDomDocument doc("XFile");

  QDomElement root = doc.createElement("file");
  doc.appendChild(root);
  QDomText nameT = doc.createTextNode(this->filePath);
  root.appendChild(nameT);
  
  return doc;
}
