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
#include <QtDebug>
#include <qapplication.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qtemporaryfile.h>

QString userFilePrompt() {
  int ret = QMessageBox::warning(0,
								 "AgentGUI",
								 "No model files given. To select an existing model file to edit, press OK, CANCEL otherwise.",
								 QMessageBox::Ok | QMessageBox::Cancel,
								 QMessageBox::Ok);
  if(ret == QMessageBox::Cancel){
	return QString("");
  }
  return QFileDialog::getOpenFileName(0,
									  "Open File",
									  ".",
									  "XML Files (*.xml);;Text Files (*.txt *.asc);;All Files (*.*)");
}


int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  app.setWindowIcon(QIcon(":/icons/xmme/images/euracelogo.png"));

  QString filePath = "";
  if(app.arguments().size() == 1){
	//filePath = userFilePrompt();
  }
  else{
	qDebug() << "Opening: " << app.arguments().at(1);
	filePath = app.arguments().at(1);
  }
  XMMEMainWindow w(filePath);
  w.show();
  
  return app.exec();
}
