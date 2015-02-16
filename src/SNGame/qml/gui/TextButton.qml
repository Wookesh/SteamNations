import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

MenuButton {
	id: textButton
	property var text
	
	source: "qrc:///textButton"
	
	Text {
		id: mainText
		text: textButton.text
		font.family: snFont.name
		font.pixelSize: textButton.height * 2 / 5
		color: "palegoldenrod" //TODO find proper color
		anchors.verticalCenter: parent.verticalCenter
		anchors.horizontalCenter: parent.horizontalCenter
		z: 1
	}
	
	Text {
		id: shadowText
		text: textButton.text
		font.family: snFont.name
		font.pixelSize: textButton.height * 2 / 5
		color: "black"
		anchors.left: mainText.left
		anchors.top: mainText.top
		anchors.leftMargin: 5
		anchors.topMargin: 5
	}
}
