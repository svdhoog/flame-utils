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

#ifndef XM_H
#define XM_H

#include <QObject>

/**
 * General definitions for XMachines Model class hierarchy.
 */

namespace XM {

  enum NodeType {
	XNothing,
	XModel,
	XModelList,
	XEnvironment,
	XFile,
	XFileList,
	XTimeUnit,
	XTimeUnitList,
	XDataType,
	XDataTypeList,
	XAgent,
	XAgentList,
	XMessage,
	XIOMessage,
	XMessageList,
	XInMessageList,
	XOutMessageList,
	XVariable,
	XVariableList,
	XFunction,
	XFunctionList
  };

};

#endif
