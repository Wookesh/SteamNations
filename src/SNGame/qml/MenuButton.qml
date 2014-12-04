import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Image {
	Layout.preferredHeight: sourceSize.height
	Layout.preferredWidth: sourceSize.width
	antialiasing: true
	Layout.alignment: Qt.AlignCenter
	
	signal clicked();
	
	MouseArea {
		anchors.fill: parent
		onClicked:
			parent.clicked();
	}
}
