import QtQuick 2.3

Image {
	property var iconSource;
	property var paramValue;
	
	source: "qrc:///frameSmall"
	width: sourceSize.width * root.globalScale.width
	height: sourceSize.height * root.globalScale.height
	
	Image {
		id: icon
		source: parent.iconSource
		width: sourceSize.width * root.globalScale.width
		height: sourceSize.height * root.globalScale.height
		anchors.verticalCenter: parent.verticalCenter
		anchors.left: parent.left
		anchors.leftMargin: 15
	}
	
	Text {
		id: value
		text: parent.paramValue
		font.family: snFont.name
		font.pixelSize: icon.height / 2
		anchors.left: icon.right
		anchors.verticalCenter: parent.verticalCenter
	}
}