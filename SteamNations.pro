TEMPLATE = app

QT += qml quick

SOURCES += src/SNGame/main.cpp

RESOURCES += src/SNGame/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
