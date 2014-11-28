import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
	id: gameBoard
	width: parent.width
	height: parent.height
	color: "green"
	antialiasing: true



Rectangle {
	height: parent.height
	width: parent.width
	id:scene
		 MouseArea {
			 anchors.fill: parent
			 drag.target: parent;
			 drag.minimumX: 0
			 drag.maximumX: parent.width
			 drag.minimumY: 0
			 drag.maximumY: parent.height
			 drag.filterChildren: true
			 acceptedButtons: Qt.AllButtons
			 onWheel:
				scene.scale += wheel.angleDelta.y / 1000


				 Rectangle {
					 id: krab
					 width: 100; height: 100
					 color: "red"

					 antialiasing: true
					 SpriteSequence {
						 id: sprite
						 width: 64
						 height: 64
						 interpolate: false
						 goalSprite: ""

						 Sprite {
							 name: "idle"
							 source: "../melee-idle.png"
							 frameCount: 8
							 frameDuration: 64
						 }
					 }

				 }

		 }
	 }
	signal exit()

	Button {
		text: "Quit"
		onClicked:
			gameBoard.exit()
	}
}
