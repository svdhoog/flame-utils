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

#ifndef XDATATYPE_H
#define XDATATYPE_H

#include <QObject>
#include <qdom.h>
#include "XDataTypeList.h"
#include "XVariableList.h"

/**
 * C++ Header File Template.
 *
 * Ignore this.
 */

class XDataType : public QObject {

Q_OBJECT

public:

  //////////////////
  // CONSTRUCTORS //
  //////////////////

  /**
   * Default constructor.
   */
  //XDataType();

  /**
   * Constructor consuming the parent.
   */
  XDataType(XDataTypeList *tmp);

  /**
   * Constructor consuming a DomNode.
   */
  XDataType(QDomDocument& dom, XDataTypeList *tmp);

  /**
   * Deconstructor.
   */
  ~XDataType();

  /////////////////////////
  // SETTERS AND GETTERS //
  /////////////////////////

  /**
   * Gets the top level model.
   */

  XModel* getTopLevelModel() const;

  /**
   * Sets the dataType name.
   */
  void setName(const QString &name);

  /**
   * Gets the dataType name.
   */
  QString getName() const;

  /**
   * Sets the dataType description.
   */
  void setDescription(const QString &description);

  /**
   * Gets the dataType description.
   */
  QString getDescription() const;

  /**
   * Sets parent dataType list.
   *
   * @see parent
   */
  void setParent(XDataTypeList *parent);

  /**
   * Gets parent dataType list.
   *
   * @see parent
   */
  XDataTypeList * getParent() const;
  /**
   * Sets children variable list.
   *
   * @see variables
   */

  void setVariables(XVariableList *parent);

  /**
   * Gets children variable list.
   *
   * @see variables
   */

  XVariableList * getVariables() const;

  //////////////////////
  // PUBLIC VARIABLES //
  //////////////////////
  
  //QList<XVariable *> variables;

  ///////////////////
  // OTHER METHODS //
  ///////////////////

  /**
   * Returns a string representation of this.
   */
  QString toString() const;

  /**
   * Returns a string representation of this at the given depth.
   */
  QString toString(int) const;

  /**
   * Returns an HTML representation of this.
   */
  QString toHTML() const;

  /**
   * Returns a Dom Document representing this data type.
   */
  QDomDocument toDomDocument() const;

private:

  /**
   * DataType name.
   */
  QString name;

  /**
   * DataType description.
   */
  QString description;

  /**
   * Parent dataType list.
   */
  XDataTypeList * parent;

   /**
   * XVariable children of the  dataType.
   */
  XVariableList * variables;
};

#endif

