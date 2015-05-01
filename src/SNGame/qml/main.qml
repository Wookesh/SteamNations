import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import SN 1.0
import SNGM 1.0 as SN

Rectangle {
	id: root

	property variant globalScale: Qt.size(initialSize.height / 1080, initialSize.width / 1920)
	
	FontLoader {
		id: snFont
		source: "qrc:///TrashBarusa.ttf"
	}
	
	CreateGame {
		id: createGame
		visible: false
		onBack: {
			createGame.visible = false
			mainMenu.visible = true
		}
		onStart: {
			createGame.visible = false
			gameUI.focus = true;
			gameUI.visible = true
		}
		onGameLoaded: {
			createGame.visible = false
			gameUI.focus = true;
			gameUI.visible = true
		}
	}
	
	GameUI {
		id: gameUI
		visible: false
		onExit: {
			gameUI.visible = false
			mainMenu.visible = true
			SN.gm.endGame()
		}
	}

	MainMenu {
		id: mainMenu
		visible: true
		onNewGameClicked: {
			createGame.visible = true
			mainMenu.visible = false
		}
	}
}
