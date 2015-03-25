import QtQuick 2.3

Item {
	id: container
	property alias cellColor: rectangle.color
	signal clicked(color cellColor)

	width: 80; height: 50

	Rectangle {
		id: rectangle
		border.color: "white"
		anchors.fill: parent
	}

	MouseArea {
		anchors.fill: parent
		onClicked: 
			container.clicked(container.cellColor)
	}
 }