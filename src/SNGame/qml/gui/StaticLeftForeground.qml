import QtQuick 2.3

Image {
	source: "qrc:///leftForeground"
	width: sourceSize.width * root.globalScale.width
	height: sourceSize.height * root.globalScale.height
}