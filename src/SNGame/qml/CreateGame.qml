import QtQuick 2.3
import QtQuick.Layouts 1.1
import SN 1.0
import "./gui"

Rectangle {
	id: createGame
	anchors.fill: parent
	
	signal back()
	signal start()
	signal gameLoaded()
	
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
	
	function tryToStart() {
		var playerNames = [];
		var playerColors = [];
		var playerAI = [];
		for (var i = 0; i < gameData.playersCount; ++i) {
			playerNames[i] = gameData.entries[i].name;
			playerColors[i] = gameData.entries[i].color;
			playerAI[i] = gameData.entries[i].computer;
		}
		gmib.gameManager.useSettings(gameData.boardWidth, gameData.boardHeight, gameData.playersCount, playerNames, playerAI, playerColors);
		createGame.start();
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
		property var boardHeight: 30
		property var boardWidth: 30
		property var entries: [p1, p2, p3, p4]
		
		PlayerDataEntry {
			id: p1
			name: "Player1"
		}
		PlayerDataEntry {
			id: p2
			name: "Player2"
		}
		PlayerDataEntry {
			id: p3
			name: "Player3"
		}
		PlayerDataEntry {
			id: p4
			name: "Player4"
		}
		Row {
			spacing: 20
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
		}
		anchors.horizontalCenter: parent.horizontalCenter
		
		Component.onCompleted: {
			p3.disabled = true;
			p4.disabled = true;
		}
	}
	
	Row {
		spacing: 20
		anchors.top: gameData.bottom
		anchors.horizontalCenter: parent.horizontalCenter
		
		Component.onCompleted:
			mediumMap.check()
		
		function uncheckAll() {
			smallMap.uncheck()
			mediumMap.uncheck()
			largeMap.uncheck()
		}
		
		StateButton {
			id: smallMap
			text: "Small"
			onClicked: {
				gameData.boardWidth = 15
				gameData.boardHeight = 15
				parent.uncheckAll()
				smallMap.check()
			}
		}
		
		StateButton {
			id: mediumMap
			text: "Medium"
			onClicked: {
				gameData.boardWidth = 30
				gameData.boardHeight = 30
				parent.uncheckAll()
				mediumMap.check()
			}
		}
		
		StateButton {
			id: largeMap
			text: "Large"
			onClicked: {
				gameData.boardWidth = 50
				gameData.boardHeight = 50
				parent.uncheckAll()
				largeMap.check()
			}
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
			id: startButton
			text: "Start"
			onClicked:
				createGame.tryToStart();
		}
		
		TextButton {
			id: load
			text: "Load"
			onClicked: {
				gmib.gameManager.load("/home/wookesh/TestSave.sn")
				createGame.gameLoaded()
			}
	}
	}
	
}
