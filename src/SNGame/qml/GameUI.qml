import QtQuick 2.3
import QtQuick.Controls 1.2
import "./gui"
import SN 1.0

Rectangle {
	id: gameUI
	focus: true
	width: parent.width
	height: parent.height
	antialiasing: true

	StaticLeftForeground {
		id: staticLeftForeground
		z: 1
		
		MenuButton {
			id: menuButton
			source: "qrc:///menuButton"
			
			onClicked:
				gameUI.exit()
		}
		
		MenuButton {
			id: techButton
			source: "qrc:///techButton"
			anchors.top: menuButton.bottom
			
			onClicked:
				console.log("TechButton clicked\n")
		}
		
		MenuButton {
			id: playerButton
			source: "qrc:///playersInfo"
			anchors.top: techButton.bottom
			
			onClicked:
				console.log("PlayersInfoButton clicked\n")
		}
		
		
		ParamDisplay {
			id: goldDisplay
			iconSource: "qrc:///gold"
			paramValue: 10
			anchors.top: playerButton.bottom
			anchors.right: playerButton.right
		}
		
		ParamDisplay {
			id: researchDisplay
			iconSource: "qrc:///research"
			paramValue: 10
			anchors.top: goldDisplay.bottom
			anchors.right: goldDisplay.right
		}
		
		ParamDisplay {
			id: foodDisplay
			iconSource: "qrc:///food"
			paramValue: 10
			anchors.top: researchDisplay.bottom
			anchors.right: researchDisplay.right
		}
		
		NextTurnButton {
			id: nextTurnButton
			x: -nextTurnButton.width / 3
			y: staticLeftForeground.height - (nextTurnButton.width * 1 / 2)
		}
	}
	
	ObjectInfoBox {
		id: objectInfoBox
		x: gameUI.width - objectInfoBox.width 
		z: 1
	}
	
	MouseArea {
		anchors.fill: parent
		drag.target: scene;
		drag.minimumX: parent.width - scene.width * (1 + scene.scale) / 2
		drag.maximumX: menuButton.width + 80 * scene.scale - scene.width * (1 - scene.scale) / 2
		drag.minimumY: parent.height - scene.height * (1 + scene.scale) / 2
		drag.maximumY: 70 * scene.scale - scene.height * (1 - scene.scale) / 2
		acceptedButtons: Qt.AllButtons
		onWheel: {
			if (wheel.angleDelta.y > 0) {
				if (scene.scale < 2)
					scene.scale += 0.05
			} else {
				if (scene.scale > 0.5)
					scene.scale -= 0.05
			}
			if (scene.x < drag.minimumX)
				scene.x = drag.minimumX
			if (scene.x > drag.maximumX)
				scene.x = drag.maximumX
			if (scene.y < drag.minimumY)
				scene.y = drag.minimumY
			if (scene.y > drag.maximumY)
				scene.y = drag.maximumY
			
		}

		onClicked: {
			scene.click(mouseX, mouseY, scene.x, scene.y, scene.scale)
		}

		property Board scene;

		Board {
			width: 5960
			height: 6920
			x: -2000
			y: -3000
			id: scene
			
			function setBoard() {
				scene.width = scene.boardWidth;
				scene.height = scene.boardHeight;
				scene.x = (1920 * root.globalScale.width - scene.width) / 2 + menuButton.width;
				scene.y = (1080 * root.globalScale.height - scene.height) / 2;
			}
			
			Component.onCompleted: {
				gameConsole.createConnections();
				nextTurnButton.createConnections();
				objectInfoBox.createConnections();
				scene.boardSet.connect(scene.setBoard);
			}
		}
	}
	
	GameConsole {
		id: gameConsole
		visible: false
	}
	
	Keys.onPressed: {
		if (event.key == Qt.Key_QuoteLeft) {
			gameConsole.visible = !gameConsole.visible;
			event.accepted = true;
			gameConsole.getFocus();
		}
	}

	signal exit()
}
