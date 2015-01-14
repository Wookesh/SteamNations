import QtQuick 2.3
import QtQuick.Controls 1.2
import SN 1.0

Image {

	id:objectInfoBox
	property InfoBox snInfoBox;
	property var owner : "undefined"
	property var name  : "undefined"
	property var nameBoxHeight : 180 * root.globalScale.height
	property var boxWidth: 220 * root.globalScale.width
	
	function objectChanged() {
		objectInfoBox.owner = snInfoBox.owner
		objectInfoBox.name = snInfoBox.name
		settle.visible = false;
		settler.visible = false;
		infantry.visible = false;
		heavy.visible = false;
		artillery.visible = false;
		if (snInfoBox.actions.length) {
			for (var i = 0; i < snInfoBox.actions.length; i++) {
				if (snInfoBox.actions[i] == "Settle") 
					settle.visible = true;
				if (snInfoBox.actions[i] == "Settler") 
					settler.visible = true;
				if (snInfoBox.actions[i] == "Infantry") 
					infantry.visible = true;
				if (snInfoBox.actions[i] == "Heavy") 
					heavy.visible = true;
				if (snInfoBox.actions[i] == "Artillery") 
					artillery.visible = true;
			}
		}
	}
	
	function visibleChanged() {
		objectInfoBox.visible = snInfoBox.visible
	}
	
	function createConnections() {
		snInfoBox = scene.infobox;
		snInfoBox.objectChanged.connect(objectInfoBox.objectChanged);
		snInfoBox.visibleChanged.connect(objectInfoBox.visibleChanged);
	}
	
	visible: false
	source: "qrc:///infoBoxBackground"
	width: sourceSize.width * root.globalScale.width
	height: sourceSize.height * root.globalScale.height
	
	Column {
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.top: objectInfoBox.top
		anchors.topMargin: (objectInfoBox.nameBoxHeight - objectName.height - playerName.height) / 2
		Label {
			id: objectName
			text: objectInfoBox.name
			anchors.horizontalCenter: parent.horizontalCenter
			font.family: snFont.name
			font.pixelSize: 32
			color: "white"
		}
	
		Label {
			id: playerName
			text:"Player: " + objectInfoBox.owner
			anchors.horizontalCenter: parent.horizontalCenter
			font.family: snFont.name
			font.pixelSize: 32
			color: "white"
		}
	}
	
	Column {
		id: iconColumn
		anchors.top: objectInfoBox.top
		anchors.topMargin: objectInfoBox.nameBoxHeight
		anchors.right: objectInfoBox.right
		anchors.rightMargin: objectInfoBox.boxWidth / 2
		
		MenuButton {
			id:settle
			source:"qrc:///unit/Town";
			onClicked: scene.makeAction(0)
		}
		
		MenuButton {
			id:settler
			source:"qrc:///unit/Settler";
			onClicked:scene.makeAction(0);
		}
		
		MenuButton {
			id:infantry
			source:"qrc:///unit/Infantry";
			onClicked:scene.makeAction(1);
		}
		
		MenuButton {
			id:heavy
			source:"qrc:///unit/Heavy";
			onClicked:scene.makeAction(2);
		}
		
		MenuButton {
			id:artillery
			source:"qrc:///unit/Artillery";
			onClicked:scene.makeAction(3);
		}
	
	}
}

