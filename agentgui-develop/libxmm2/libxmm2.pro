# Copyright (C) 2007, 2008 Vehbi Sinan Tunalioglu <vst@vsthost.com>
# 
# This file is part of libxmm2.
# 
# libxmm2 is free software; you can redistribute it andor modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# libxmm2 is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with libxmm2; if not, write to the Free Software Foundation,
# Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

VERSION = 0.0.3

TEMPLATE = lib
TARGET = xmm2

CONFIG += qt dll
CONFIG += debug_and_release
CONFIG += build_all
CONFIG += warn_on

QT += xml
QT -= gui

DESTDIR = "./lib"

MOC_DIR = "./compilation"
OBJECTS_DIR = "./compilation"
RCC_DIR = "./compilation"
UI_DIR = "./compilation"
UI_HEADERS_DIR = "./compilation"
UI_SOURCES_DIR = "./compilation"

INCLUDEPATH = "." "./include"

win32 {
    CONFIG += release
}


HEADERS = \
  ./include/XM.h \
  ./include/XModel.h \
  ./include/XModelList.h \
  ./include/XEnvironment.h \
  ./include/XFile.h \
  ./include/XFileList.h \
  ./include/XTimeUnit.h \
  ./include/XTimeUnitList.h \
  ./include/XDataType.h \
  ./include/XDataTypeList.h \
  ./include/XAgent.h \
  ./include/XAgentList.h \
  ./include/XMessage.h \
  ./include/XIOMessage.h \
  ./include/XMessageList.h \
  ./include/XInMessageList.h \
  ./include/XOutMessageList.h \
  ./include/XVariable.h \
  ./include/XVariableList.h \
  ./include/XFunction.h \
  ./include/XFunctionList.h \
  ./include/auxiliary.h \
  ./include/globals.h \
  ./include/errors.h

SOURCES = \
  ./src/XModel.cpp \
  ./src/XModelList.cpp \
  ./src/XEnvironment.cpp \
  ./src/XFile.cpp \
  ./src/XFileList.cpp \
  ./src/XTimeUnit.cpp \
  ./src/XTimeUnitList.cpp \
  ./src/XDataType.cpp \
  ./src/XDataTypeList.cpp \
  ./src/XAgent.cpp \
  ./src/XAgentList.cpp \
  ./src/XMessage.cpp \
  ./src/XIOMessage.cpp \
  ./src/XMessageList.cpp \
  ./src/XInMessageList.cpp \
  ./src/XOutMessageList.cpp \
  ./src/XVariable.cpp \
  ./src/XVariableList.cpp \
  ./src/XFunction.cpp \
  ./src/XFunctionList.cpp \
  ./src/auxiliary.cpp
