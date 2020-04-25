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

#ifndef XFILE_H
#define XFILE_H

#include <QObject>
#include <qdom.h>

class XFileList;
class XModel;

/**
 * XModels container.
 */

class XFile : public QObject {

Q_OBJECT

public:

  //////////////////
  // CONSTRUCTORS //
  //////////////////

  /**
   * Default constructor.
   */

  //XFile(XModel *parent);

  /**
   * Constructor consuming the parent.
   */

  XFile(XFileList * parent);

  /**
   * Constructor consuming the path of the file.
   */

  XFile(QString filePath, XFileList * parent);

  /**
   * Deconstructor.
   */
  ~XFile();

  /////////////////////////
  // SETTERS AND GETTERS //
  /////////////////////////

  /**
   * Gets the top level model.
   */

  XModel* getTopLevelModel() const;

  /**
   * Sets parent fileList.
   *
   * @see parent
   */
  void setParent(XFileList *parent);

  /**
   * Gets parent fileList.
   *
   * @see parent
   */
  XFileList * getParent() const;

  /**
   * Sets the filePath.
   */
  void setFilePath(const QString& filePath);

  /**
   * Gets the filePath.
   */
  QString getFilePath() const;

  //////////////////
  // PUBLIC FILES //
  //////////////////

  QString filePath;

  ///////////////////
  // OTHER METHODS //
  ///////////////////

  /**
   * Returns a string representation of this.
   */
  QString toString() const;

  /**
   * Returns a string representation of this with lines indented by depth.
   */
  QString toString(int depth) const;

  /**
   * Returns an HTML description list representation of this.
   */
  QString toHTML() const;

  /**
   * Returns a Dom Document representing this file list.
   */
  QDomDocument toDomDocument() const;

private:

  XFileList *parent;

};

#endif
