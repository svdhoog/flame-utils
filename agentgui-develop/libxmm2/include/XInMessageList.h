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

#ifndef XINMESSAGELIST_H
#define XINMESSAGELIST_H

#include <QObject>
#include <qdom.h>

class XModel;
class XMessage;
class XIOMessage;
class XFunction;

/**
 * XModels container.
 */

class XInMessageList : public QObject {

Q_OBJECT

public:

  //////////////////
  // CONSTRUCTORS //
  //////////////////

  /**
   * Default constructor.
   */

  //XInMessageList(XModel *parent);

  /**
   * Constructor consuming Dom document representing a list of XMessages
   */

  XInMessageList(XFunction * parent);

  /**
   * Deconstructor.
   */
  ~XInMessageList();

  /////////////////////////
  // SETTERS AND GETTERS //
  /////////////////////////

  /**
   * Gets the top level model.
   */

  XModel* getTopLevelModel() const;

  /**
   * Sets parent model.
   *
   * @see parent
   */
  void setParent(XFunction *parent);

  /**
   * Gets parent model.
   *
   * @see parent
   */
  XFunction * getParent() const;

  /**
   * Gets the message with the given name.
   */
  XMessage * getMessageByName(QString name);

  //////////////////////
  // PUBLIC VARIABLES //
  //////////////////////

  QList<XIOMessage *> messageList;

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
   * Returns a Dom Document representing this in messages list
   */
  QDomDocument toDomDocument() const;

private:

  XFunction *parent;

};

#endif
