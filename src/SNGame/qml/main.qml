import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import SN 1.0

Rectangle {
	id: root

	property variant globalScale: Qt.size(initialSize.height / 1080, initialSize.width / 1920)

	Component.onCompleted: console.log(snFont.status == FontLoader.Ready)
	
	FontLoader {
		id: snFont
		source: "qrc:///TrashBarusa.ttf"
	}
	
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
