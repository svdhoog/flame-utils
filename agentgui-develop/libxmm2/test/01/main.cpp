///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2007 Vehbi Sinan Tunalioglu <vst@vsthost.com>           //
//                                                                       //
// This file is part of XMMLEditor.                                      //
//                                                                       //
// XMMLEditor is free software; you can redistribute it and/or modify    //
// it under the terms of the GNU General Public License as published     //
// by the Free Software Foundation; either version 2 of the License,     //
// or (at your option) any later version.                                //
//                                                                       //
// XMMLEditor is distributed in the hope that it will be useful, but     //
// WITHOUT ANY WARRANTY; without even the implied warranty of            //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     //
// General Public License for more details.                              //
//                                                                       //
// You should have received a copy of the GNU General Public License     //
// along with XMMLEditor; if not, write to the Free Software Foundation, //
// Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA          //
///////////////////////////////////////////////////////////////////////////


#include <qapplication.h>
#include <qdebug.h>
#include <QFile>
#include <QStringList>
#include <XModel.h>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv, FALSE);

  if(app.arguments().size() == 1){
  	qDebug() << "No model files given. Closing the test suite.";
  	return 1;
  }

  if(QFile::exists(app.arguments().at(1))){
    XModel *model = new XModel(app.arguments().at(1));
	for(int i = 0; i < model->pendingMsgInits.size(); i++){
	  qDebug() << model->pendingMsgInits.at(i)->messageName << model->pendingMsgInits.at(i)->msgPointer;
	}

	QFile file("/tmp/out.html");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
	  qDebug() << "Cannot open file to write.";
	  return 1;
	}
	
	QTextStream out(&file);
	out << model->toHTML();
  }
  
  return app.exec();
}

