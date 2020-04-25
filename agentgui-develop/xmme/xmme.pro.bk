TEMPLATE = app
DEPENDPATH += "." "src"
INCLUDEPATH += "." "../libxmm2/include/"
TARGET = agentgui

unix {
    LIBS += -lxmm2 -L"../libxmm2/lib/"
    LIBS += -lqscintilla2
    CONFIG += debug
    INCLUDEPATH += "/usr/include/qt4/Qsci/" \
      "/usr/local/Cellar/qscintilla2/2.8/include/" \
      "/usr/local/Cellar/qscintilla2/2.8/include/Qsci"
}

win32 {
    LIBS += ../../libxmm2/trunk/lib/xmm20.dll
    LIBS += -lqscintilla2
    CONFIG += release
    INCLUDEPATH += "c:/Qt/4.4.3/include/Qsci/"
    RC_FILE = xmme.rc
}

QT += xml

# Input
FORMS += \
  "ui/XWidgetEditModel.ui" \
  "ui/XWidgetEditAgent.ui" \
  "ui/XWidgetEditVariable.ui" \
  "ui/XWidgetEditFunction.ui" \
  "ui/XWidgetEditFunctionInMessages.ui" \
  "ui/XWidgetEditFunctionOutMessages.ui" \
  "ui/XWidgetEditMessage.ui" \
  "ui/XWidgetEditIOMessage.ui" \
  "ui/XWidgetEditTimeUnit.ui" \
  "ui/XWidgetEditFile.ui" \
  "ui/XWidgetEditDataType.ui" \
  "ui/XMMEMainWindow.ui"

HEADERS += \
  "src/XModelView.h" \
  "src/XModelTree.h" \
  "src/XWidgetEditModel.h" \
  "src/XWidgetEditAgent.h" \
  "src/XWidgetEditVariable.h" \
  "src/XWidgetEditFunction.h" \
  "src/XWidgetEditFunctionInMessages.h" \
  "src/XWidgetEditFunctionOutMessages.h" \
  "src/XWidgetEditMessage.h" \
  "src/XWidgetEditIOMessage.h" \
  "src/XWidgetEditTimeUnit.h" \
  "src/XWidgetEditFile.h" \
  "src/XWidgetEditDataType.h" \
  "src/XMMEMainWindow.h" \
  "src/globals.h"

SOURCES += \
  "src/XMMEMainWindow.cpp" \
  "src/XModelView.cpp" \
  "src/XModelTree.cpp" \
  "src/main.cpp"

RESOURCES += \
  "xmme.qrc"

DESTDIR = "./compilation"
MOC_DIR = "./compilation"
OBJECTS_DIR = "./compilation"
RCC_DIR = "./compilation"
UI_DIR = "./compilation"
UI_HEADERS_DIR = "./compilation"
UI_SOURCES_DIR = "./compilation"

#include(../../modeltest/modeltest.pri)
