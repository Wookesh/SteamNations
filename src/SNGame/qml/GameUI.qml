import QtQuick 2.3
import QtQuick.Controls 1.2
import "./gui"
import SN 1.0

Rectangle {
	id: gameUI
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
			anchors.horizontalCenter: playerButton.horizontalCenter
		}
		
		ParamDisplay {
			id: researchDisplay
			iconSource: "qrc:///research"
			paramValue: 10
			anchors.top: goldDisplay.bottom
			anchors.horizontalCenter: goldDisplay.horizontalCenter
		}
		
		ParamDisplay {
			id: foodDisplay
			iconSource: "qrc:///food"
			paramValue: 10
			anchors.top: researchDisplay.bottom
			anchors.horizontalCenter: researchDisplay.horizontalCenter
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
		drag.minimumX: parent.width - scene.width
		drag.maximumX: 0
		drag.minimumY: parent.height - scene.height
		drag.maximumY: 0
		acceptedButtons: Qt.AllButtons
		onWheel: {
			if (wheel.angleDelta.y > 0) {
				if (scene.scale < 1)
					scene.scale += 0.05
			} else {
				if (scene.scale > 0.1)
					scene.scale -= 0.05
			}
		}

		onClicked: {
			console.log(mouseX + " " + mouseY + "\n")
		}

		
		Board {
			width: 5000
			height: 5000
			x: -2500
			y: -2500
			id: scene
		}
	}

	signal exit()
}
