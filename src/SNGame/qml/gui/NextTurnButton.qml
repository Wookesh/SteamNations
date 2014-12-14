import QtQuick 2.3

Item {
	id: nextTurnButton
	width: trybik.width
	height: trybik.height
	
	property bool rotating: true
	
	signal nextTurn()
	
	Image {
		id: trybik
		source: "qrc:///trybik"
		width: sourceSize.width * root.globalScale.width
		height: sourceSize.height * root.globalScale.height
		x: 0
		y: 0
	}
	
	Timer {
		id: rotationTimer
		interval: 1000
		repeat: true
		running: true
		
		onTriggered: {
			trybik.rotation = trybik.rotation + 9
		}
	}
	
	MenuButton {
		id: nextTurn
		source: "qrc:///playButtonBlue"
		anchors.centerIn: parent
		
		onClicked: {
			console.log("Next turn clicked\n")
			nextTurnButton.nextTurn()
		}
	}
	
	onRotatingChanged: {
		if (rotating)
			rotationTimer.start();
		else
			rotationTimer.stop();
	}
}