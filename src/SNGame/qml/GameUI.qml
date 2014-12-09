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
			y: menuButton.height
			
			onClicked:
				console.log("TechButton clicked\n")
		}
		
		MenuButton {
			id: playerButton
			source: "qrc:///playersInfo"
			y: techButton.height + techButton.y
			
			onClicked:
				console.log("PlayersInfoButton clicked\n")
		}
		
		NextTurnButton {
			id: nextTurnButton
			x: -nextTurnButton.width / 3
			y: staticLeftForeground.height - (nextTurnButton.width * 2 / 3)
		}
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
			height: 5000
			width: 5000
			x: -1000
			y: -1000
			id: scene
		}
	}

	signal exit()
}
