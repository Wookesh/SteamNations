TEMPLATE = app

QT += qml quick

CONFIG += c++11

SOURCES += src/SNGame/main.cpp \  
    src/SNGame/Board.cpp

RESOURCES += src/SNGame/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/SNGame/Board.hpp
