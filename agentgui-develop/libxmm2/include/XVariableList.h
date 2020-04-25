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

#ifndef XVARIABLELIST_H
#define XVARIABLELIST_H

#include <QObject>
#include <qdom.h>

class XModel;
class XMessage;
class XVariable;

/**
 * XModels container.
 */

class XVariableList : public QObject {

Q_OBJECT

public:

  //////////////////
  // CONSTRUCTORS //
  //////////////////

  /**
   * Default constructor consuming the parent QObject of this.
   */
  XVariableList(QObject *parent = 0);

  /**
   * Constructor consuming Dom document representing a list of XVariables
   */
  XVariableList(QDomDocument &dom, QObject * parent);

  /**
   * Deconstructor.
   */
  ~XVariableList();

  /////////////////////////
  // SETTERS AND GETTERS //
  /////////////////////////

  /**
   * Gets the top level model.
   */
  XModel* getTopLevelModel() const;

  /**
   * Sets parent message.
   *
   * @see parent
   */
  void setParent(QObject *parent);

  /**
   * Gets parent message.
   *
   * @see parent
   */
  QObject * getParent() const;

  //////////////////////
  // PUBLIC VARIABLES //
  //////////////////////

  QList<XVariable *> variableList;

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
   * Returns a Dom Document representing this variable list.
   */
  QDomDocument toDomDocument(const QString &wrapperTag = "variables") const;

private:

  QObject *parent;

};

#endif
