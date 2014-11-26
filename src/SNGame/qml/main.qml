import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle {
	width: 640;
	height: 480;


	GameBoard {
		id: gameBoard
		visible: false
		onExit: {
			gameBoard.visible = false
			mainMenu.visible = true
		}
	}

	MainMenu {
		id: mainMenu
		onNewGameClicked: {
			gameBoard.visible = true
			mainMenu.visible = false
		}
	}

//	ColumnLayout {

//		visible: true
//		id: mainLayout

//		anchors.centerIn: parent
//		spacing: 10

//		MenuButton {
//			id: newGame
//			text: "New game"
//			onClicked:
//				gameBoard.visible = true,
//				mainLayout.visible = false
//		}

//		MenuButton {
//			id: loadGame
//			text: "Load game"
//		}

//		MenuButton {
//			id: options
//			text: "Options"
//		}

//		MenuButton {
//			id: exit
//			text: "Exit"
//			onClicked: Qt.quit();
//		}
//	}
}
