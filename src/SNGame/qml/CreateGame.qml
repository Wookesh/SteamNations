import QtQuick 2.3
import QtQuick.Layouts 1.1
import "./gui"

Rectangle {
	id: createGame
	anchors.fill: parent
	
	signal back()
	signal start()
	
	function addPlayer() {
		if (gameData.playersCount < 4) {
			gameData.entries[gameData.playersCount].disabled = false;
			++gameData.playersCount;
		}
	}
	
	function removePlayer() {
		if (gameData.playersCount > 2) {
			--gameData.playersCount;
			gameData.entries[gameData.playersCount].disabled = true;
		}
	}
	
	Image {
		id: background
		source: "qrc:///menuBackground"
		antialiasing: true
		anchors.fill: parent
	}
	
	Column {
		id: gameData
		property var playersCount: 2
		property var entries: [p1, p2, p3, p4]
		
		PlayerDataEntry {
			id: p1
		}
		PlayerDataEntry {
			id: p2
		}
		PlayerDataEntry {
			id: p3
		}
		PlayerDataEntry {
			id: p4
		}
		anchors.horizontalCenter: parent.horizontalCenter
		
		Component.onCompleted: {
			p3.disabled = true;
			p4.disabled = true;
		}
	}
	
	Row {
		anchors.bottom: parent.bottom
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
			onClicked:
				createGame.addPlayer()
		}
		
		TextButton {
			id: removeButton
			text: "Remove Player"
			onClicked:
				createGame.removePlayer()
		}
		
		TextButton {
			id: startButton
			text: "Start"
			onClicked:
				createGame.start();
		}
	}
	
}
