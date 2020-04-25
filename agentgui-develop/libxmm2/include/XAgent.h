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

#ifndef XAGENT_H
#define XAGENT_H

#include <QObject>
#include <qdom.h>

class XModel;
class XAgentList;
class XVariableList;
class XFunctionList;

/**
 * C++ Header File Template.
 *
 * Ignore this.
 */

class XAgent : public QObject {

Q_OBJECT

public:

  //////////////////
  // CONSTRUCTORS //
  //////////////////

  /**
   * Default constructor.
   */
  //XAgent();

  /**
   * Constructor consuming the parent.
   */
  XAgent(XAgentList * parent = 0);
  
  /**
   * Constructor consuming a DomNode.
   */
  XAgent(QDomDocument &dom, XAgentList * parent = 0);
  
  /**
   * Deconstructor.
   */
  ~XAgent();

  /////////////////////////
  // SETTERS AND GETTERS //
  /////////////////////////

  /**
   * Gets the top level model.
   */

  XModel* getTopLevelModel() const;

  /**
   * Sets the agent name.
   */
  void setName(const QString& name);

  /**
   * Gets the agent name.
   */
  QString getName() const;

  /**
   * Sets the agent description.
   */
  void setDescription(const QString& description);

  /**
   * Gets the agent description.
   */
  QString getDescription() const;

  /**
   * Sets the agent's parent.
   */
  void setParent(XAgentList *parent);

  /**
   * Gets the agent's parent.
   */
  XAgentList* getParent() const;

  /**
   * Sets children variable list of the agent (namely the agent
   * memory).
   *
   * @see variables
   */

  void setVariables(XVariableList *parent);

  /**
   * Gets children variable list of the agent (namely the agent
   * memory).
   *
   * @see variables
   */

  XVariableList * getVariables() const;

  /**
   * Sets children function list of the agent (namely the agent
   * memory).
   *
   * @see functions
   */

  void setFunctions(XFunctionList *parent);

  /**
   * Gets children function list of the agent (namely the agent
   * memory).
   *
   * @see functions
   */

  XFunctionList * getFunctions() const;

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
   * Returns a string representation of this formatted at the given
   * depth.
   */
  QString toString(int depth) const;

  /**
   * Returns an HTML representation of this.
   */
  QString toHTML() const;

  /**
   * Returns a Dom Document representing this agent.
   */
  QDomDocument toDomDocument() const;

private:

  /**
   * Agent name.
   */
  QString name;

  /**
   * Agent description.
   */
  QString description;

  /**
   * Agent's parent.
   */
  XAgentList * parent;

  /**
   * XVariable children of the agent (namely the agent memory).
   */
  XVariableList * variables;
  
  /**
   * XFunction children of the agent (namely the agent memory).
   */
  XFunctionList * functions;
  
};

#endif
