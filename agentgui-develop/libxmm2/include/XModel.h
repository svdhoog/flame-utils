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

#ifndef XMODEL_H
#define XMODEL_H

#include <QObject>
#include <qdom.h>
#include <XIOMessage.h>

class XEnvironment;
class XModelList;
class XAgent;
class XAgentList;
class XMessage;
class XMessageList;
class QDir;

/**
 * Entire model specification.
 *
 * This class is the core of the X-Machines Model data. It holds
 * everything which belongs to the model, together with some meta
 * information needed.
 */
class XModel : public QObject {

Q_OBJECT

public:

  //////////////////
  // CONSTRUCTORS //
  //////////////////

  /**
   * Default constructor consuming parent.
   */
  XModel(XModelList *parent = 0);
  
  /**
   * Constructor consuming a file path to model XML to initialize the
   * instance.
   */
  XModel(const QString &modelXMLFilePath, XModelList * parent = 0);

  /**
   * Deconstructor.
   */
  ~XModel();

  /////////////////////////
  // SETTERS AND GETTERS //
  /////////////////////////

  /**
   * Gets the top level model.
   */

  XModel* getTopLevelModel();

  /**
   * Gets the name of the model.
   *
   * @see name
   */
  QString getName() const;

  /**
   * Sets the name of the model.
   *
   * @see name
   */
  void setName(const QString &name);

  /**
   * Gets the enabled flag of the model.
   *
   * @see enabled
   */
  bool getEnabled() const;

  /**
   * Sets the enabled flag of the model.
   *
   * @see enabled
   */
  void setEnabled(bool enabled);

   /**
   * Gets the version of the model.
   *
   * @see version
   */
  QString getVersion() const;

  /**
   * Sets the version of the model.
   *
   * @see version
   */
  void setVersion(const QString &version);

  /**
   * Gets model description.
   *
   * @see description
   */
  QString getDescription() const;

  /**
   * Sets model description.
   *
   * @see description
   */
  void setDescription(const QString &description);

  /**
   * Gets model file path.
   *
   * @see filePath
   */
  QString getFilePath() const;

  /**
   * Sets model file path.
   *
   * @see filePath
   */
  void setFilePath(const QString &filePath);

  /**
   * Gets parent model.
   *
   * @see parent
   */
  XModel * getParentModel() const;

  /**
   * Gets parent model list.
   *
   * @see parent
   */
  XModelList * getParent() const;

  /**
   * Sets parent model list.
   *
   * @see parent
   */
  void setParent(XModelList *parent);

  /**
   * Adds a new nested model.
   */

  void addModel(XModel *model);

  /**
   * Returns the number of nested models for this model.
   */

  int nestedModelCount();

  /**
   * Returns the nested model at the given offset. If not found,
   * returns NULL.
   */

  XModel * getModelAt(int index);

  /**
   * Returns the nested model with the given name. If not found,
   * returns NULL.
   */

  XModel * getModelByName(QString name);

  /**
   * Removes the model at the given offset. If none to be removed,
   * no side effects produced.
   */

  void removeModelAt(int index);

  /**
   * Removes the model with the given name. If none to be removed, no
   * side effects produced.
   */

  void removeModelByName(QString name);

  /**
   * Sets the nested model list of the model.
   */

  void setNestedModels(XModelList *modelList);

  /**
   * Gets the nested model list of the model.
   */

  XModelList * getNestedModels() const;

  /**
   * Sets the environment to the model.
   */

  void setEnvironment(XEnvironment *environment);

  /**
   * Gets the environment to the model.
   */

  XEnvironment* getEnvironment();

  /**
   * Adds a new agent to the model.
   */

  void addAgent(XAgent *agent);

  /**
   * Returns the number of agents defined in this model.
   */

  int agentCount();

  /**
   * Returns the agent at the given offset. If not found,
   * returns NULL.
   */

  XAgent * getAgentAt(int index);

  /**
   * Returns the agent with the given name. If not found,
   * returns NULL.
   */

  XAgent * getAgentByName(QString name);

  /**
   * Removes the agent at the given offset. If none to be removed,
   * no side effects produced.
   */

  void removeAgentAt(int index);

  /**
   * Removes the agent with the given name. If none to be removed, no
   * side effects produced.
   */

  void removeAgentByName(QString name);

  /**
   * Sets the agents list of the model.
   */

  void setAgents(XAgentList *agentList);

  /**
   * Gets the agents list of the model.
   */

  XAgentList * getAgents() const;

  /**
   * Adds a new message to the model.
   */

  void addMessage(XMessage *message);

  /**
   * Returns the number of messages defined in this model.
   */

  int messageCount();

  /**
   * Returns the message at the given offset. If not found,
   * returns NULL.
   */

  XMessage * getMessageAt(int index);

  /**
   * Returns the message with the given name. If not found,
   * returns NULL.
   */

  XMessage * getMessageByName(QString name);

  /**
   * Removes the message at the given offset. If none to be removed,
   * no side effects produced.
   */

  void removeMessageAt(int index);

  /**
   * Removes the message with the given name. If none to be removed, no
   * side effects produced.
   */

  void removeMessageByName(QString name);

  /**
   * Sets the messages list of the model.
   */

  void setMessages(XMessageList *messageList);

  /**
   * Gets the messages list of the model.
   */

  XMessageList * getMessages() const;

  /**
   * Gets the messages list of the model and its nested models.
   */

  QList<XMessage*> getAllMessages();

  /**
   * Gets model file directory.
   *
   * @see filePath
   */
  QDir getFileDir() const;

  //////////////////////
  // PUBLIC VARIABLES //
  //////////////////////

  /**
   * Holds a list of pending XIOMessages waiting for XMessage
   * definitions.
   */
  QList<XIOMessage*> pendingMsgInits;

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
   * Returns a Dom Document representing this entire model.
   */
  QDomDocument toDomDocument() const;

  /**
   * Saves the entire model and nested ones.
   */
  bool save();

private:

  /**
   * Model name.
   */
 
  QString name;

  /**
   * Version label. To differ from other models by assigning a
   * meaningful name.
   */
  
  QString version; 

  /**
   * A short description of the model.
   */
  
  QString description;

  /**
   * List of nested models.
   */

  XModelList * nestedModels;

  /**
   * Environment specification for the current model.
   */

  XEnvironment * environment;

  /**
   * List of agents for the model
   */

  XAgentList * agents;

  /**
   * List of messages for the model
   */

  XMessageList * messages;

//   /**
//    * List of contexts for the model
//    */
//   XContextList contexts;

  /**
   * Specifies model XML path on the file system for this model.
   */
  
  QString filePath;

  /**
   * Specifies the parent XModelList of this.
   */
  XModelList *parent;

  /**
   * Specifies if the model is enabled or not.
   */
  bool enabled;

};

#endif
