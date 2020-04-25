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

#ifndef XVARIABLE_H
#define XVARIABLE_H

#include <QObject>
#include <qdom.h>
#include "XVariableList.h"

/**
 * C++ Header File Template.
 *
 * Ignore this.
 */

class XVariable : public QObject {

Q_OBJECT

public:

  //////////////////
  // CONSTRUCTORS //
  //////////////////

  /**
   * Default constructor.
   */
  //XVariable();

  /**
   * Constructor consuming the parent.
   */
  XVariable(XVariableList *tmp);

  /**
   * Constructor consuming a DomNode.
   */
  XVariable(QDomDocument& dom, XVariableList *tmp);

  /**
   * Deconstructor.
   */
  ~XVariable();

  /////////////////////////
  // SETTERS AND GETTERS //
  /////////////////////////

  /**
   * Gets the top level model.
   */

  XModel* getTopLevelModel() const;

  /**
   * Sets the variable type.
   */
  void setType(const QString &type);

  /**
   * Gets the variable type.
   */
  QString getType() const;

  /**
   * Sets the variable name.
   */
  void setName(const QString &name);

  /**
   * Gets the variable name.
   */
  QString getName() const;

  /**
   * Sets the variable description.
   */
  void setDescription(const QString &description);

  /**
   * Gets the variable description.
   */
  QString getDescription() const;

  /**
   * Sets parent variable list.
   *
   * @see parent
   */
  void setParent(XVariableList *parent);

  /**
   * Gets parent variable list.
   *
   * @see parent
   */
  XVariableList * getParent() const;


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
   * Returns a Dom Document representing this variable.
   */
  QDomDocument toDomDocument() const;

private:

  /**
   * Variable type.
   */
  QString type;

  /**
   * Variable name.
   */
  QString name;

  /**
   * Variable description.
   */
  QString description;

  /**
   * Parent variable list.
   */
  XVariableList * parent;
};

#endif

