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

#ifndef XTIMEUNIT_H
#define XTIMEUNIT_H

#include <QObject>
#include <qdom.h>
#include "XTimeUnitList.h"

/**
 * C++ Header File Template.
 *
 * Ignore this.
 */

class XTimeUnit : public QObject {

Q_OBJECT

public:

  //////////////////
  // CONSTRUCTORS //
  //////////////////

  /**
   * Default constructor.
   */
  //XTimeUnit();

  /**
   * Constructor consuming the parent.
   */
  XTimeUnit(XTimeUnitList *tmp);

  /**
   * Constructor consuming a DomNode.
   */
  XTimeUnit(QDomDocument& dom, XTimeUnitList *tmp);

  /**
   * Deconstructor.
   */
  ~XTimeUnit();

  /////////////////////////
  // SETTERS AND GETTERS //
  /////////////////////////

  /**
   * Gets the top level model.
   */

  XModel* getTopLevelModel() const;

  /**
   * Sets the timeUnit name.
   */
  void setName(const QString &name);

  /**
   * Gets the timeUnit name.
   */
  QString getName() const;

  /**
   * Sets the timeUnit unit.
   */
  void setUnit(const QString &unit);

  /**
   * Gets the timeUnit unit.
   */
  QString getUnit() const;

  /**
   * Sets the timeUnit period.
   */
  void setPeriod(const QString &period);

  /**
   * Gets the timeUnit period.
   */
  QString getPeriod() const;

  /**
   * Sets parent timeUnit list.
   *
   * @see parent
   */
  void setParent(XTimeUnitList *parent);

  /**
   * Gets parent timeUnit list.
   *
   * @see parent
   */
  XTimeUnitList * getParent() const;


  //////////////////////
  // PUBLIC TIMEUNITS //
  //////////////////////
  
  //QList<XTimeUnit *> timeUnits;

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
   * Returns a Dom Document representing this timeUnit.
   */
  QDomDocument toDomDocument() const;

private:

  /**
   * TimeUnit name.
   */
  QString name;

  /**
   * TimeUnit unit.
   */
  QString unit;

  /**
   * TimeUnit period.
   */
  QString period;

  /**
   * Parent timeUnit list.
   */
  XTimeUnitList * parent;
};

#endif

