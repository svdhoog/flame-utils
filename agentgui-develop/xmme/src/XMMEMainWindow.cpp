////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2008 Vehbi Sinan Tunalioglu <vst@vsthost.com>           //
//                                                                        //
//  This file is part of xmme.                                            //
//                                                                        //
//  xmme is free software: you can redistribute it and/or                 //
//  modify it under the terms of the GNU General Public License           //
//  as published by the Free Software Foundation, either version 3        //
//  of the License, or (at your option) any later version.                //
//                                                                        //
//  xmme is distributed in the hope that it will be useful, but           //
//  WITHOUT ANY WARRANTY; without even the implied warranty of            //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     //
//  General Public License for more details.                              //
//                                                                        //
//  You should have received a copy of the GNU General Public License     //
//  along with xmme.  If not, see <http://www.gnu.org/licenses/>.         //
////////////////////////////////////////////////////////////////////////////

#include "XMMEMainWindow.h"
#include "XModelTree.h"
#include "XWidgetEditAgent.h"
#include "XWidgetEditDataType.h"
#include "XWidgetEditFile.h"
#include "XWidgetEditFunction.h"
#include "XWidgetEditFunctionInMessages.h"
#include "XWidgetEditFunctionOutMessages.h"
#include "XWidgetEditMessage.h"
#include "XWidgetEditIOMessage.h"
#include "XWidgetEditModel.h"
#include "XWidgetEditTimeUnit.h"
#include "XWidgetEditVariable.h"
#include "globals.h"
#include <XModel.h>
//#include <modeltest.h>
#include <qmessagebox.h>
#include <qregexp.h>
#include <qprocess.h>
#include <qtextedit.h>
#include <qevent.h>

QString formattedHTML(QString in);

XMMEMainWindow::XMMEMainWindow(QString filePath){

  ////////////////////////
  // DEFAULT OPERATIONS //
  ////////////////////////

  setupUi(this);

  /////////////
  // MAKE-UP //
  /////////////

  ////////////////////////
  // BIND SIGNALS-SLOTS //
  ////////////////////////

  connect(actionNew, SIGNAL(triggered()), this, SLOT(actionSlotNew()));
  connect(actionOpen, SIGNAL(triggered()), this, SLOT(actionSlotOpen()));
  connect(actionSave, SIGNAL(triggered()), this, SLOT(actionSlotSave()));
  connect(actionQuoit, SIGNAL(triggered()), this, SLOT(actionSlotQuit()));
  connect(actionAbout, SIGNAL(triggered()), this, SLOT(actionSlotAbout()));

  toolBar->addAction(actionNew);
  toolBar->addAction(actionOpen);
  toolBar->addAction(actionSave);
  toolBar->addAction(actionQuoit);

  //////////////////////////
  // INITIALIZE THE XMODEL //
  //////////////////////////

  // TODO: Check if the file path given resolves to a valid Model
  // file.
  if(QFile::exists(filePath)){
	this->model = new XModel(filePath);

	///////////////////////////////////////
	// CREATE and SET THE MODEL FOR VIEW //
	///////////////////////////////////////

	this->viewModel = new XModelTree(this->model);
	//new ModelTest(this->viewModel, this);
	this->modelView->setModel(this->viewModel);
	this->informationView->setHtml(model->toHTML());
  }
  else{
	this->model = new XModel();
	this->model->setName("New Model");
	///////////////////////////////////////
	// CREATE and SET THE MODEL FOR VIEW //
	///////////////////////////////////////

	this->viewModel = new XModelTree(this->model);
	//new ModelTest(this->viewModel, this);
	this->modelView->setModel(this->viewModel);
	this->informationView->setHtml(model->toHTML());
  }
  ////////////////
  // START VIEW //
  ////////////////

  this->modelView->setParentWindow(this);
}

void XMMEMainWindow::showInfo(QString info){
  QString tmp;
  tmp = "<html>";
  tmp += "<head>";
  tmp += "<style>";
  tmp += "body {font-size: 8pt; background-color:#DEDEDE; margin: 0px; padding:0px} h1 {font-size: 10pt}";
  tmp += "</style>";
  tmp += "</head>";
  tmp += "<body topmargin=0 leftmargin=0>";
  tmp += info;
  tmp += "</body>";
  tmp += "</html>";

  //this->informationView->setPlainText(tmp);
  //this->informationView->setHtml(formattedHTML(info));
  this->informationView->setPlainText(info);
}

QString formattedHTML(QString in){
  // TODO: Buggy
  in.replace(QRegExp("<([^>]+)>([^<>]*)</([^>]+)>"), "<font color=red>&lt;\\1&gt;</font>\\2<font color=red>&lt;/\\3&gt;</font>");
  return in;
}

void XMMEMainWindow::emptyEditingLayout(){
  if(this->editing->layout()){
	QLayoutItem *child;
	while ((child = this->editing->layout()->takeAt(0)) != 0) {
	  if(child->widget()){
		delete child->widget();
		delete child;
	  }
	}
	delete this->editing->layout();
  }
}

void XMMEMainWindow::editModel(XModel *model, const QModelIndex &index){
  this->emptyEditingLayout();

  QVBoxLayout *layout = new QVBoxLayout;
  XWidgetEditModel* editWidget = new XWidgetEditModel(model, index);
  layout->addWidget(editWidget);
  this->editing->setLayout(layout);

  connect(editWidget, SIGNAL(dataChanged(const QModelIndex &)), this, SLOT(dataChanged(const QModelIndex &)));
}

void XMMEMainWindow::editAgent(XAgent *agent, const QModelIndex &index){
  this->emptyEditingLayout();

  QVBoxLayout *layout = new QVBoxLayout;
  XWidgetEditAgent* editWidget = new XWidgetEditAgent(agent, index);
  layout->addWidget(editWidget);
  this->editing->setLayout(layout);

  connect(editWidget, SIGNAL(dataChanged(const QModelIndex &)), this, SLOT(dataChanged(const QModelIndex &)));
}

void XMMEMainWindow::editVariable(XVariable *variable, const QModelIndex &index){
  this->emptyEditingLayout();

  QVBoxLayout *layout = new QVBoxLayout;
  XWidgetEditVariable* editWidget = new XWidgetEditVariable(variable, index);
  layout->addWidget(editWidget);
  this->editing->setLayout(layout);

  connect(editWidget, SIGNAL(dataChanged(const QModelIndex &)), this, SLOT(dataChanged(const QModelIndex &)));
}

void XMMEMainWindow::editFunction(XFunction *function, const QModelIndex &index){
  this->emptyEditingLayout();

  QVBoxLayout *layout = new QVBoxLayout;
  XWidgetEditFunction* editWidget = new XWidgetEditFunction(function, index);
  layout->addWidget(editWidget);
  this->editing->setLayout(layout);

  connect(editWidget, SIGNAL(dataChanged(const QModelIndex &)), this, SLOT(dataChanged(const QModelIndex &)));
}

void XMMEMainWindow::editMessage(XMessage *message, const QModelIndex &index){
  this->emptyEditingLayout();

  QVBoxLayout *layout = new QVBoxLayout;
  XWidgetEditMessage* editWidget = new XWidgetEditMessage(message, index);
  layout->addWidget(editWidget);
  this->editing->setLayout(layout);

  connect(editWidget, SIGNAL(dataChanged(const QModelIndex &)), this, SLOT(dataChanged(const QModelIndex &)));
}

void XMMEMainWindow::editIOMessage(XIOMessage *IOmessage, const QModelIndex &index){
  this->emptyEditingLayout();

  QVBoxLayout *layout = new QVBoxLayout;
  XWidgetEditIOMessage* editWidget = new XWidgetEditIOMessage(IOmessage, index);
  layout->addWidget(editWidget);
  this->editing->setLayout(layout);

  connect(editWidget, SIGNAL(dataChanged(const QModelIndex &)), this, SLOT(dataChanged(const QModelIndex &)));
}

void XMMEMainWindow::editInputMessages(XInMessageList *inList, const QModelIndex &index){
  this->emptyEditingLayout();

  QVBoxLayout *layout = new QVBoxLayout;
  XWidgetEditFunctionInMessages* editWidget = new XWidgetEditFunctionInMessages(inList, index);
  layout->addWidget(editWidget);
  this->editing->setLayout(layout);

  connect(editWidget, SIGNAL(dataChanged(const QModelIndex &)), this, SLOT(dataChanged(const QModelIndex &)));
}

void XMMEMainWindow::editOutputMessages(XOutMessageList *outList, const QModelIndex &index){
  this->emptyEditingLayout();

  QVBoxLayout *layout = new QVBoxLayout;
  XWidgetEditFunctionOutMessages* editWidget = new XWidgetEditFunctionOutMessages(outList, index);
  layout->addWidget(editWidget);
  this->editing->setLayout(layout);

  connect(editWidget, SIGNAL(dataChanged(const QModelIndex &)), this, SLOT(dataChanged(const QModelIndex &)));
}

void XMMEMainWindow::editTimeUnit(XTimeUnit *timeUnit, const QModelIndex &index){
  this->emptyEditingLayout();

  QVBoxLayout *layout = new QVBoxLayout;
  XWidgetEditTimeUnit* editWidget = new XWidgetEditTimeUnit(timeUnit, index);
  layout->addWidget(editWidget);
  this->editing->setLayout(layout);

  connect(editWidget, SIGNAL(dataChanged(const QModelIndex &)), this, SLOT(dataChanged(const QModelIndex &)));
}

void XMMEMainWindow::editFile(XFile *file, const QModelIndex &index){
  this->emptyEditingLayout();

  QVBoxLayout *layout = new QVBoxLayout;
  XWidgetEditFile* editWidget = new XWidgetEditFile(file, index);
  layout->addWidget(editWidget);
  this->editing->setLayout(layout);

  connect(editWidget, SIGNAL(dataChanged(const QModelIndex &)), this, SLOT(dataChanged(const QModelIndex &)));
}

void XMMEMainWindow::editDataType(XDataType *dataType, const QModelIndex &index){
  this->emptyEditingLayout();

  QVBoxLayout *layout = new QVBoxLayout;
  XWidgetEditDataType* editWidget = new XWidgetEditDataType(dataType, index);
  layout->addWidget(editWidget);
  this->editing->setLayout(layout);

  connect(editWidget, SIGNAL(dataChanged(const QModelIndex &)), this, SLOT(dataChanged(const QModelIndex &)));
}

void XMMEMainWindow::dataChanged(const QModelIndex &index){
  this->viewModel->setData(index, QVariant());
  this->modelView->displayXMML(index);
}

void XMMEMainWindow::editNull(){
  this->emptyEditingLayout();
}

void XMMEMainWindow::actionSlotNew(){
  QApplication *myapp = (QApplication*)QCoreApplication::instance();
  QProcess xmme;
  if(!xmme.startDetached(myapp->arguments()[0], QStringList())){
	QMessageBox::critical(0, SOFTWARE_NAME,
						  QString("Could not create a new process."),
						  QMessageBox::Close);
  }
// #ifdef Q_WS_WIN
//   qDebug() << "Detected Win platform";
//   xmme.startDetached(myapp->arguments()[0], QStringList());
// #else
//   qDebug() << "Detected NonWin platform";
//   xmme.startDetached(myapp->arguments()[0], QStringList());
// #endif
}

void XMMEMainWindow::actionSlotOpen(){
  QString fileToOpen = QFileDialog::getOpenFileName(0,
													"Open File",
													".",
													"XML Files (*.xml);;Text Files (*.txt *.asc);;All Files (*.*)");
  if(fileToOpen == ""){
	return;
  }
  QApplication *myapp = (QApplication*)QCoreApplication::instance();
  QProcess xmme;
  if(!xmme.startDetached(myapp->arguments()[0], QStringList() << fileToOpen)){
	QMessageBox::critical(0, SOFTWARE_NAME,
						  QString("Could not create a new process."),
						  QMessageBox::Close);
  }
}

void XMMEMainWindow::actionSlotSave(){
  qDebug() << "Model File Path" << this->model->getFilePath();
  if(this->model->getFilePath() == ""){
	qDebug() << "Model File Path is not given yet. Prompting.";
	QString fileToSave = QFileDialog::getSaveFileName(0,
													  "Choose Path to Save File",
													  ".",
													  "XML Files (*.xml);;Text Files (*.txt *.asc);;All Files (*.*)");
	if(fileToSave == ""){
	  qDebug() << "User has cancelled. Returning.";
	  return;
	}
	this->model->setFilePath(fileToSave);
  }
  this->model->save();
}

void XMMEMainWindow::actionSlotQuit(){
  this->close();
}

void XMMEMainWindow::actionSlotAbout(){
  QMessageBox::information(0, SOFTWARE_NAME,
						   QString("AgentGUI - X Machines Modeling Editor (a.k.a XMME)\n\n")+
						   "Developed by TUBITAK/UEAKE\n" +
						   "For feedbacks and feature requests:\n" +
						   "Vehbi Sinan Tunalioglu <vst@vsthost.com>\n\n"
						   "Version of this build is: " +
						   VERSION_MAJOR + "." + VERSION_MINOR + "." + VERSION_BUILD + " " + SVN_REVISION_ID,
						   QMessageBox::Close);
}

void XMMEMainWindow::closeEvent(QCloseEvent *event){
  int ret = QMessageBox::warning(0,
								 "AgentGUI",
								 "Are you sure you want to exit the program?",
								 QMessageBox::Yes | QMessageBox::Cancel,
								 QMessageBox::Cancel);
  if(ret == QMessageBox::Cancel){
	event->ignore();
	return;
  }
  event->accept();
}
