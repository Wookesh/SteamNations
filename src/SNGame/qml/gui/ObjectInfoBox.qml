import QtQuick 2.3
import QtQuick.Controls 1.2
import SN 1.0

SNImage {

	id:objectInfoBox
	property InfoBox snInfoBox;
	property var owner : "undefined"
	property var name  : "undefined"
	property var nameBoxHeight : 180 * root.globalScale.height
	property var boxWidth: 220 * root.globalScale.width
	
	function unitChanged() {
		healthBar.visible = true;
		healthBarFull.y = healthBarFull.height * (snInfoBox.health-snInfoBox.healthLeft) / snInfoBox.health;
		healthBarFullText.text = snInfoBox.healthLeft + "/" + snInfoBox.health;
		
	}
	
	function objectChanged() {
		healthBar.visible = false;
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
		snInfoBox.unitChanged.connect(objectInfoBox.unitChanged);
	}
	
	visible: false
	source: "qrc:///infoBoxBackground"
	
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
	
	SNImage{
		visible:false
		id:healthBar
		clip:true
		scale:0.7;
		source:"qrc:///healthBar";
		x:objectInfoBox.width-boxWidth+(boxWidth-width)/2;
		y:nameBoxHeight*2;
		
		SNImage{
			id:healthBarFull
			z:-1
			source:"qrc:///healthBarFull";
			y:100
		}
		
		Label{
			id:healthBarFullText
			text:"10/20";
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter 
			font.family: snFont.name
			font.pixelSize: 40
			rotation:90;
			
		}
	}
}

