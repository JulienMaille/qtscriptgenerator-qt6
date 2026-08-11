TARGET = qtscript_svg
include(../qtbindingsbase.pri)
QT += gui widgets svg svgwidgets
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_svg/com_trolltech_qt_svg.pri)
