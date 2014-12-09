import QtQuick 2.3

Image {
	source: "qrc:///leftForeground"
	height: sourceSize.height * root.globalScale
	width: sourceSize.width * root.globalScale
	x: 0
	y: 0
	Component.onCompleted: console.log(root.globalScale)
}