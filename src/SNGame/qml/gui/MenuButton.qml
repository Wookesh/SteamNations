import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Image {
	Layout.preferredHeight: height.height
	Layout.preferredWidth: width.width
	Layout.alignment: Qt.AlignCenter
	
	antialiasing: true
	height: sourceSize.height * root.globalScale
	width: sourceSize.width * root.globalScale
	x: 0
	y: 0
	
	signal clicked();
	
	MouseArea {
		anchors.fill: parent
		onClicked:
			parent.clicked();
	}
}
