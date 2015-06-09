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
	property var labelSize:20
	
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
// 		anchors.top: objectInfoBox.top
// 		anchors.topMargin: objectInfoBox.nameBoxHeight
// 		anchors.left: objectInfoBox.left+objectInfoBox.width-objectInfoBox.boxWidth
// 		anchors.leftMargin: 0
		
		x:objectInfoBox.width*1.05-objectInfoBox.boxWidth
		y:nameBoxHeight
		MenuButton {
			id:settle
			source:"qrc:///unit/Town";
			onClicked: scene.makeAction(0)
		}
		

		Row{
			id:infantry
			MenuButton {
				source:"qrc:///unit/Infantry";
				onClicked:scene.makeAction(0);
				Label {
					text:"25"
					y:parent.height-this.height
					font.family: snFont.name
					font.pixelSize: labelSize
					color: "white"
				}
			}
		}
		Row{
			id:heavy
			MenuButton {
				source:"qrc:///unit/Heavy";
				onClicked:scene.makeAction(1);
				Label {
					text:"50"
					y:parent.height-this.height
					font.family: snFont.name
					font.pixelSize: labelSize
					color: "white"
				}
			}
		}
		Row{
			id:artillery
			MenuButton {
				source:"qrc:///unit/Artillery";
				onClicked:scene.makeAction(2);
				Label {
					text:"100"
					y:parent.height-this.height
					font.family: snFont.name
					font.pixelSize: labelSize
					color: "white"
				}
			}
		}
		Row{
			id:settler
			MenuButton {
				source:"qrc:///unit/Settler";
				onClicked:scene.makeAction(3);
				Label {
					text:"200"
					y:parent.height-this.height
					font.family: snFont.name
					font.pixelSize: labelSize
					color: "white"
				}
			}
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

