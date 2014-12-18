import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Image {
	Layout.alignment: Qt.AlignCenter
	
	antialiasing: true
	width: sourceSize.width * root.globalScale.width * root.globalScale.width
	height: sourceSize.height * root.globalScale.height * root.globalScale.height
	x: 0
	y: 0
	
	signal clicked();
	
	MouseArea {
		anchors.fill: parent
		onClicked:
			parent.clicked();
	}
}
