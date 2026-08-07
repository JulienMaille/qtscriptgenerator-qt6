TARGET = qtscript_network
include(../qtbindingsbase.pri)
QT -= gui
QT += network
DEFINES += QTSCRIPT_NETWORK_PACKAGE
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_network/com_trolltech_qt_network.pri)
