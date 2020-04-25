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

#ifndef XAGENTLIST_H
#define XAGENTLIST_H

#include <QObject>
#include <qdom.h>

class XModel;
class XAgent;

/**
 * XModels container.
 */

class XAgentList : public QObject {

Q_OBJECT

public:

  //////////////////
  // CONSTRUCTORS //
  //////////////////

  /**
   * Default constructor consuming the parent XModel of this.
   */
  XAgentList(XModel *parent = 0);

  /**
   * Constructor consuming Dom document representing a list of XAgents
   */
  XAgentList(QDomDocument &dom, XModel * parent = 0);

  /**
   * Deconstructor.
   */
  ~XAgentList();

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

  //////////////////////
  // PUBLIC VARIABLES //
  //////////////////////

  QList<XAgent *> agentList;

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
   * Returns a Dom Document representing this agent list.
   */
  QDomDocument toDomDocument() const;

private:

  XModel *parent;

};

#endif
