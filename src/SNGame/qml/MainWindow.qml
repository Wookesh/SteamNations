import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Item {
	width: 640;
	height: 480;
	id: mainMenu

	ColumnLayout {
		anchors.centerIn: parent
		spacing: 10
		
		Button {
			id: newGame
			width: 200
			height: 50
			text: "New game"
			antialiasing: true
			Layout.alignment: Qt.AlignCenter
		}
		
		Button {
			id: loadGame
			width: 200
			height:50
			text: "Load game"
			antialiasing: true
			Layout.alignment: Qt.AlignCenter
		}

		Button {
			id: options
			width: 200
			height:50
			text: "Options"
			antialiasing: true
			Layout.alignment: Qt.AlignCenter
		}

		Button {
			id: exit
			width: 200
			height:50
			text: "Exit"
			antialiasing: true
			Layout.alignment: Qt.AlignCenter
		}
	}
}