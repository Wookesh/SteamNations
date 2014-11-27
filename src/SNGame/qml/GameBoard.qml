import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
	id: gameBoard
	width: parent.width
	height: parent.height
	color: "green"
	
	property int currentX: 0
	property int currentY: 0

	signal exit()

	Button {
		z: 1
		text: "Quit"
		onClicked:
			gameBoard.exit()
	}
	
	MouseArea {
		anchors.fill: parent
		
		property int initialX: 0
		property int initialY: 0
		
		onClicked:
			console.log("currnetPos = " + gameBoard.currentX + ", " + gameBoard.currentY  + "\n")
		
		onPressed: {
			initialX = mouseX
			initialY = mouseY
		}
		
		onReleased: {
			gameBoard.currentX += initialX - mouseX
			gameBoard.currentY += initialY - mouseY
		}
		
		onPositionChanged: {
			console.log("\n\tx = " + mouseX + "\n\ty = " + mouseY)
		}
	}
}
