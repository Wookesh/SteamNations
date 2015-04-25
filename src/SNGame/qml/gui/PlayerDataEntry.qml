import QtQuick 2.3
import QtQuick.Controls 1.2
import "./colorPicker"

Row {
	id: entry
	height: 2 * colorPicker.height
	property bool disabled: false
	property alias color: colorPicker.cellColor
	property alias name: nameBox.text
	property alias computer:ai.checked
	
	StateButton {
		id:ai
		text: "AI"
		onClicked:{
			if (checked)
				ai.uncheck();
			else
				ai.check();
		}
		height:parent.height
		width:ai.height
		
	}

	
	TextField {
		id: nameBox
		height: frame.height
		width: frame.width
		enabled: !entry.disabled
		text: "Player"
		textColor: "black"
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
			disabled: entry.disabled
			anchors.right: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
		}
	}
	anchors.horizontalCenter: parent.horizontalCenter
}