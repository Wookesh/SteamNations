import QtQuick 2.3
import QtQuick.Layouts 1.1
import "./gui"

Rectangle {
	id: createGame
	width: parent.width
	height: parent.height

	signal back()
	signal start()
	
	function addPlayer() {
		
	}
	
	Image {
		id: background
		source: "qrc:///menuBackground"
		antialiasing: true
		anchors.fill: parent
	}
	
	Column {
		id: gameData
		spacing: 20
		
		PlayerDataEntry {
		}
		
	}
	
	Row {
		anchors.top: gameData.bottom
		anchors.horizontalCenter: parent.horizontalCenter
		spacing: 20
		
		TextButton {
			id: backButton
			text: "Back"
			onClicked:
				createGame.back();
		}
		
		TextButton {
			id: addButton
			text: "Add Player"
		}
		
		TextButton {
			id: startButton
			text: "Start"
			onClicked:
				createGame.start();
		}
	}
	
}
