import QtQuick 2.3
import QtQuick.Layouts 1.1
import "./gui"

Rectangle {
	id: mainMenu
	width: parent.width
	height: parent.height

	signal newGameClicked()


	RowLayout {
		anchors.centerIn: parent
		
		Image {
			Layout.preferredWidth: sourceSize.width
			source: "qrc:///logo"
		}
		
		ColumnLayout {
			Layout.preferredWidth: newGame.Layout.preferredWidth
			
			MenuButton {
				id: newGame
				onClicked:
					mainMenu.newGameClicked();
				source: "qrc:///startButton"
			}

			MenuButton {
				id: exit
				onClicked: Qt.quit();
				source: "qrc:///exitButton"
			}
		}
	}
}
