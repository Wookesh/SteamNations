import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle {
	width: 1280;
	height: 720;

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
		visible:true
		onNewGameClicked: {
			gameBoard.visible = true
			mainMenu.visible = false
		}
	}


}
