import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import SN 1.0

Rectangle {
	id: root
	
	width: 1280;
	height: 720;

	property var globalScale: width / 1920;

	GameUI {
		id: gameUI
		visible: false
		onExit: {
			gameUI.visible = false
			mainMenu.visible = true
		}
	}

	MainMenu {
		id: mainMenu
		visible: true
		onNewGameClicked: {
			gameUI.visible = true
			mainMenu.visible = false
		}
	}


}
