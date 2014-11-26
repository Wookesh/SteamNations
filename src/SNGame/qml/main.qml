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

		MenuButton {
			id: newGame
			text: "New game"
		}

		MenuButton {
			id: loadGame
			text: "Load game"
		}

		MenuButton {
			id: options
			text: "Options"
		}

		MenuButton {
			id: exit
			text: "Exit"
			onClicked: Qt.quit();
		}


	}
}
