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

#ifndef XFUNCTION_H
#define XFUNCTION_H

#include <QObject>
#include <qdom.h>

class XFunctionList;
class XMessageList;
class XInMessageList;
class XOutMessageList;
class XModel;

/**
 * C++ Header File Template.
 *
 * Ignore this.
 */

class XFunction : public QObject {

Q_OBJECT

public:

  //////////////////
  // CONSTRUCTORS //
  //////////////////

  /**
   * Default constructor.
   */
  //XFunction();

  /**
   * Constructor consuming a parent.
   */
  XFunction(XFunctionList * parent);

  /**
   * Constructor consuming a Dom document and a parent.
   */
  XFunction(QDomDocument &dom, XFunctionList * parent);

  /**
   * Deconstructor.
   */
  ~XFunction();

  /////////////////////////
  // SETTERS AND GETTERS //
  /////////////////////////

  /**
   * Gets the top level model.
   */

  XModel* getTopLevelModel() const;

  /**
   * Sets function's name
   */
  void setName(const QString &name);

  /**
   * Gets function's name
   */
  QString getName() const;

  /**
   * Sets function's description
   */
  void setDescription(const QString &description);

  /**
   * Gets function's description
   */
  QString getDescription() const;

  /**
   * Sets function's code
   */
  void setCode(const QString &code);
  
  /**
   * Gets function's code
   */
  QString getCode() const;

  /**
   * Sets function's currentState
   */
  void setCurrentState(const QString &currentState);
  
  /**
   * Gets function's currentState
   */
  QString getCurrentState() const;

  /**
   * Sets function's nextState
   */
  void setNextState(const QString &nextState);

  /**
   * Gets function's nextState
   */
  QString getNextState() const;

  /**
   * Sets function's condition
   */
  void setCondition(const QString &condition);
  
  /**
   * Gets function's condition
   */
  QString getCondition() const;
  
  /**
   * Sets function's parent
   */
  void setParent(XFunctionList *parent);
  
  /**
   * Gets function's parent
   */
  XFunctionList* getParent() const;
  
  /**
   * Gets function's parent model.
   */
  XModel* getParentModel() const;
  
  /**
   * Sets the messages which are consumed by this function.
   */

  void setMessagesIn(XMessageList *messageList);

  /**
   * Gets the messages which are consumed by this function.
   */

  XMessageList * getMessagesIn() const;

  /**
   * Sets the messages which are produced by this function.
   */

  void setMessagesOut(XMessageList *messageList);

  /**
   * Gets the messages which are produced by this function.
   */

  XMessageList * getMessagesOut() const;


  //////////////////////
  // PUBLIC VARIABLES //
  //////////////////////
  
  /**
   * List of messages the function consumes.
   */
  XInMessageList * messagesIn;

  /**
   * List of messages the function produces.
   */
  XOutMessageList * messagesOut;

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
  QString toString(int depth) const;

  /**
   * Returns an HTML representation of this.
   */
  QString toHTML() const;

  /**
   * Returns a Dom Document representing this function.
   */
  QDomDocument toDomDocument() const;

private:

  /**
   * Function name.
   */
  QString name;

  /**
   * Function description.
   */
  QString description;

  /**
   * Function code.
   */
  QString code;

  /**
   * Function's current state.
   */
  QString currentState;

  /**
   * Function's next state.
   */
  QString nextState;

  /**
   * Function's condition
   */
  QString condition;
  
  /**
   * Function's parent function list.
   */
  XFunctionList *parent;
  
};

#endif
