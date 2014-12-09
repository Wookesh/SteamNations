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
			source: "qrc:../images/logo_steam_nations.png"
		}
		
		ColumnLayout {
			Layout.preferredWidth: newGame.Layout.preferredWidth
			
			MenuButton {
				id: newGame
				onClicked:
					mainMenu.newGameClicked();
				source: "qrc:../images/start_button.png"
			}

			MenuButton {
				id: exit
				onClicked: Qt.quit();
				source: "qrc:../images/exit_button.png"
			}
		}
	}
}
