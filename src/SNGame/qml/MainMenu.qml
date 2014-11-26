import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
	id: mainMenu
	width: parent.width
	height: parent.height

	signal newGameClicked()


	ColumnLayout {
		anchors.centerIn: parent
		spacing: 10

		MenuButton {
			id: newGame
			text: "New game"
			onClicked:
				mainMenu.newGameClicked();
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
