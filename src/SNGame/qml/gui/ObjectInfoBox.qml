import QtQuick 2.3

Image {
	source: "qrc:///infoBoxBackground"
	width: sourceSize.width * root.globalScale.width * root.globalScale.width
	height: sourceSize.height * root.globalScale.height * root.globalScale.height
}