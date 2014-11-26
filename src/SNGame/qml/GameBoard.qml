import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
	id: gameBoard
	width: parent.width
	height: parent.height
	color: "green"

	signal exit()

	Button {
		text: "Quit"
		onClicked:
			gameBoard.exit()
	}
}
