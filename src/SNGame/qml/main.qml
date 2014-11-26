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
}
