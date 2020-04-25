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

#ifndef XIOMESSAGE_H
#define XIOMESSAGE_H

#include <QObject>
#include <qdom.h>

class XMessage;

/**
 * C++ Header File Template.
 *
 * Ignore this.
 */

class XIOMessage : public QObject {

Q_OBJECT

public:

  //////////////////
  // CONSTRUCTORS //
  //////////////////

  /**
   * Default constructor.
   */
  //XIOMessage();

  /**
   * Constructor consuming a DomNode.
   */
  XIOMessage(XMessage* msg, QObject *parent);

  /**
   * Deconstructor.
   */
  ~XIOMessage();

  //////////////////////
  // PUBLIC VARIABLES //
  //////////////////////
  
  XMessage * msgPointer;
  QObject * parent;
  QString filter;
  QString messageName;

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
   * Returns a Dom Document representing this.
   */
  QDomDocument toDomDocument() const;

private:

};

#endif

