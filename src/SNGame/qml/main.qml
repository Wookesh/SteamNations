import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    Rekt {
        anchors.centerIn: parent
        color: "red"
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}
