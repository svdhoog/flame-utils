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

#ifndef XMESSAGELIST_H
#define XMESSAGELIST_H

#include <QObject>
#include <qdom.h>

class XModel;
class XMessage;

/**
 * XModels container.
 */

class XMessageList : public QObject {

Q_OBJECT

public:

  //////////////////
  // CONSTRUCTORS //
  //////////////////

  /**
   * Default constructor consuming the parent XModel of this.
   */
  XMessageList(XModel *parent = 0);

  /**
   * Constructor consuming Dom document representing a list of XMessages
   */

  XMessageList(QDomDocument &dom, XModel * parent);

  /**
   * Deconstructor.
   */
  ~XMessageList();

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
  void setParent(XModel *parent);

  /**
   * Gets parent model.
   *
   * @see parent
   */
  XModel * getParent() const;

  /**
   * Gets the message with the given name.
   */
  XMessage * getMessageByName(QString name);

  //////////////////////
  // PUBLIC VARIABLES //
  //////////////////////

  QList<XMessage *> messageList;

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
   * Returns a Dom Document representing this message list.
   */
  QDomDocument toDomDocument() const;

private:

  XModel *parent;

};

#endif
