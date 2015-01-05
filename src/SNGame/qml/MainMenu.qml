import QtQuick 2.3
import QtQuick.Layouts 1.1
import "./gui"

Rectangle {
	id: mainMenu
	width: parent.width
	height: parent.height

	signal newGameClicked()
	
	Image {
		id: background
		source: "qrc:///menuBackground"
		antialiasing: true
		anchors.fill: parent
	}

	Image {
		id: logo
		anchors.right: background.horizontalCenter
		source: "qrc:///logo"
	}
	
	MenuButton {
		id: newGame
		onClicked:
			mainMenu.newGameClicked();
		source: "qrc:///startButton"
		anchors.right: logo.horizontalCenter
		anchors.top: logo.bottom
		anchors.rightMargin: 10
	}

	MenuButton {
		id: exit
		onClicked: Qt.quit();
		source: "qrc:///exitButton"
		anchors.verticalCenter: newGame.verticalCenter
		anchors.left: newGame.right
		anchors.leftMargin: 10
	}
}
