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

#ifndef XENVIRONMENT_H
#define XENVIRONMENT_H

#include <QObject>
#include <qdom.h>
#include <qstringlist.h>
#include <XVariableList.h>
#include <XVariable.h>
#include <XDataTypeList.h>

class XModel;
class XFileList;
class XTimeUnitList;

/**
 * C++ Header File Template.
 *
 * Ignore this.
 */

class XEnvironment : public QObject {

Q_OBJECT

public:

  //////////////////
  // CONSTRUCTORS //
  //////////////////

  /**
   * Default constructor consuming the parent XModel of this.
   */
  XEnvironment(XModel *parent = 0);

  /**
   * Constructor consuming a dom document.
   */
  XEnvironment(QDomDocument &dom, XModel * parent = 0);

  /**
   * Deconstructor.
   */
  ~XEnvironment();

  /////////////////////////
  // SETTERS AND GETTERS //
  /////////////////////////

  /**
   * Gets the top level model.
   */

  XModel* getTopLevelModel() const;

  /**
   * Gets parent model.
   *
   * @see parent
   */
  XModel * getParent() const;

  /**
   * Sets parent model.
   *
   * @see parent
   */
  void setParent(XModel *parent);

  /**
   * Gets constants.
   *
   * @see constants
   */
  XVariableList * getConstants();

  /**
   * Sets constants.
   *
   * @see constants
   */
  void setConstants(XVariableList *constants);

  /**
   * Gets functionFiles.
   *
   * @see functionFiles
   */
  XFileList * getFunctionFiles();

  /**
   * Sets functionFiles.
   *
   * @see functionFiles
   */
  void setFunctionFiles(XFileList *functionFiles);

  /**
   * Gets timeUnits.
   *
   * @see timeUnits
   */
  XTimeUnitList * getTimeUnitList();

  /**
   * Sets timeUnits.
   *
   * @see timeUnits
   */
  void setTimeUnitList(XTimeUnitList *timeUnits);

  /**
   * Gets dataTypes.
   *
   * @see dataTypes
   */
  XDataTypeList * getDataTypes();

  /**
   * Sets dataTypes.
   *
   * @see dataTypes
   */
  void setDataTypes(XDataTypeList *dataTypes);
 
  //////////////////////
  // PUBLIC VARIABLES //
  //////////////////////

  ///////////////////
  // OTHER METHODS //
  ///////////////////

  /**
   * Returns a string representation of this.
   */
  QString toString() const;

  /**
   * Returns a string representation of this with depth indented.
   */
  QString toString(int depth) const;

  /**
   * Returns an HTML representation of this.
   */
  QString toHTML() const;

  /**
   * Returns a Dom Document representing this environment.
   */
  QDomDocument toDomDocument() const;

private:

  /**
   * Model constants.
   */
  XVariableList* constants;

  /**
   * Models function files.
   */
  XFileList* functionFiles;

  /**
   * Models time units.
   */
  XTimeUnitList* timeUnits;

  /**
   * Models data types.
   */
  XDataTypeList* dataTypes;

  /**
   * Template name.
   */
  XModel * parent;
};

#endif

