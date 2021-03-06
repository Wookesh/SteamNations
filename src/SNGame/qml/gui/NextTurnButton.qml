import QtQuick 2.3
import SN 1.0
import SNGM 1.0 as SN

Item {
	id: nextTurnButton
	width: trybik.width
	height: trybik.height
	
	property bool rotating: true
	
	signal nextTurn()
	
	function createConnections() {
		nextTurn.clicked.connect(rotationTimer.start);
		nextTurn.clicked.connect(SN.gm.endTurn);
		nextTurn.clicked.connect(scene.afterTurn);
		SN.gm.turnReady.connect(rotationTimer.stop);
		SN.gm.turnReady.connect(scene.beforeTurn);
	}
	
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
		running: false
		
		onTriggered: {
			trybik.rotation = trybik.rotation + 9
		}
	}
	
	MenuButton {
		id: nextTurn
		source: "qrc:///playButtonBlue"
		anchors.centerIn: parent
	}
	
	onRotatingChanged: {
		if (rotating)
			rotationTimer.start();
		else
			rotationTimer.stop();
	}
}