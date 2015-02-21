import QtQuick 2.3
import QtQuick.Controls 1.2
import "./colorPicker"

Row {
	id: entry
	height: 4 * colorPicker.height
	property bool disabled: false
	
	TextField {
		id: nameBox
		height: frame.height
		width: frame.width
		enabled: !entry.disabled
		font.pixelSize: nameBox.height / 4
	}
	
	onDisabledChanged: {
		if (entry.disabled == false)
			entry.opacity = 1.0
		else
			entry.opacity = 0.5
	}
	
	SNImage {
		id: frame
		source: "qrc:///frameSmall"
		ColorPicker {
			id: colorPicker
			anchors.right: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
		}
	}
	anchors.horizontalCenter: parent.horizontalCenter
}