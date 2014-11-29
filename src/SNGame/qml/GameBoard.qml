import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
	id: gameBoard
	width: parent.width
	height: parent.height
	color: "green"
	antialiasing: true
	
	Component.onCompleted: {
		var component = Qt.createComponent("Crab.qml");
		var sprite;
		for (var i = 0; i < 50; ++i) {
			for (var j = 0; j < 50; ++j) {
				sprite = component.createObject(scene, {"x": 100 * [i], "y": 100 * [j]});
				if (sprite == null) {
					console.log("Error creating object");
				}
			}
		}
		console.log("All Crabs created\n");
	}

	Rectangle {
		height: 5000
		width: 5000
		x: -2500
		y: -2500
		id:scene
			MouseArea {
				anchors.fill: parent
				drag.target: parent;
				drag.minimumX: scene.parent.width - scene.width
				drag.maximumX: 0
				drag.minimumY: scene.parent.height - scene.height
				drag.maximumY: 0
				drag.filterChildren: true
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
					console.log(mouseX + " " + mouseY + " " + scene.childAt(mouseX, mouseY).width + "\n")
				}
				
				onPositionChanged: {
					console.log("SceneX = " + scene.childAt(mouseX, mouseY).x / 100)
					console.log("SceneY = " + scene.childAt(mouseX, mouseY).y / 100 + "\n")
				}

		 }
	 }
	signal exit()

	Button {
		z: 1
		text: "Quit"
		onClicked:
			gameBoard.exit()
	}
}
