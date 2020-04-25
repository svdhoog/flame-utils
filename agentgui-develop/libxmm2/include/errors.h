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

#ifndef XERROR_H
#define XERROR_H

#include <QObject>

/**
 * XError class for defining and handling errors thrown.
 *
 */

class XError : public QObject {

Q_OBJECT

public:

  /**
   * Error types
   */

  enum ErrorType {
	ModelFileNotExists,
	ModelFileNotOpened,
	ModelFileNotRead,
	ModelFileNotParsed,
	Default
  };

  /**
   * Default constructor.
   */
  XError(ErrorType et) {
	this->errorType = et;
  }

  /**
   * Deconstructor.
   */
  //~XError();

  /**
   * returns the error code;
   */

  ErrorType getErrorType(){
	return this->errorType;
  }

  /**
   * Returns a string representation of this.
   */
  QString explain() const {
	switch(this->errorType){
	case(ModelFileNotExists):
	  return "Model File does not exist";
	case(ModelFileNotOpened):
	  return "Model File can not be opened";
	default:
	  return "Unknown error";
	}
  }

private:

  /**
   * Error type.
   */
  ErrorType errorType;

  /**
   * Template name.
   */
  QString errorMessage;
};

#endif
