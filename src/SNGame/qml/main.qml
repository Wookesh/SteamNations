import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import SN 1.0

Rectangle {
	width: 640;
	height: 480;
	Timer {
			 interval: 100; running: true; repeat: true
			 onTriggered: gameBoard.update()
		 }


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
