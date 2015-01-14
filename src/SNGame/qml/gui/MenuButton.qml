import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

SNImage {
	signal clicked();
	
	MouseArea {
		anchors.fill: parent
		onClicked:
			parent.clicked();
	}
}
