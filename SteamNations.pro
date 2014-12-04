TEMPLATE = app

QT += qml quick

CONFIG += c++11

SOURCES += src/SNGame/main.cpp \ 
    src/SNGame/crab.cpp

RESOURCES += src/SNGame/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/SNGame/crab.hpp
