import QtQuick 2.3

Rectangle {
    width: 100; height: 100
    color: "red"

    MouseArea {
        anchors.fill: parent
        onClicked: console.log("Button clicked!")
    }
}