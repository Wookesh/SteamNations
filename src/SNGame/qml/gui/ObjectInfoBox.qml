import QtQuick 2.3
import QtQuick.Controls 1.2
import SN 1.0




Image {
	
	id:objectInfoBox
	property InfoBox snInfoBox;
	property var owner : "undefined"
	property var name  : "undefined"
	
	function objectChanged2() {
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
	
	function visibleChanged2() {
		objectInfoBox.visible = snInfoBox.visible
	}
	function createConnections() {
		snInfoBox = scene.infobox;
		snInfoBox.objectChanged.connect(objectInfoBox.objectChanged2);
		snInfoBox.visibleChanged.connect(objectInfoBox.visibleChanged2);
	}
	visible: false
	source: "qrc:///infoBoxBackground"
	width: sourceSize.width * root.globalScale.width * root.globalScale.width
	height: sourceSize.height * root.globalScale.height * root.globalScale.height
	Label{
		text:"Player: " + objectInfoBox.owner
		x:100
		y:30
		font.family: snFont.name
		font.pixelSize: 32
		color: "white"
	}
	
	Label{
		text: objectInfoBox.name
		x:100
		y:70
		font.family: snFont.name
		font.pixelSize: 32
		color: "white"
	}
	
	Image {
		visible:false;
		id:settle
		source:"qrc:///unit/Town";
		width: 100 ;
		height: 100;
		x:440;
		y:200;
		MouseArea {
			anchors.fill: parent;
			onClicked:scene.makeAction(0);
		}
	}
	Image {
		visible:false;
		id:settler
		source:"qrc:///unit/Settler";
		width: 100 ;
		height: 100;
		x:440;
		y:200;
		MouseArea {
			anchors.fill: parent;
			onClicked:scene.makeAction(0);
		}
	}
	Image {
		visible:false;
		id:infantry
		source:"qrc:///unit/Infantry";
		width: 100 ;
		height: 100;
		x:440;
		y:300;
		MouseArea {
			anchors.fill: parent;
			onClicked:scene.makeAction(1);
		}
	}
	Image {
		visible:false;
		id:heavy
		source:"qrc:///unit/Heavy";
		width: 100 ;
		height: 100;
		x:440;
		y:400;
		MouseArea {
			anchors.fill: parent;
			onClicked:scene.makeAction(2);
		}
	}
	Image {
		visible:false;
		id:artillery
		source:"qrc:///unit/Artillery";
		width: 100 ;
		height: 100;
		x:440;
		y:500;
		MouseArea {
			anchors.fill: parent;
			onClicked:scene.makeAction(3);
		}
	}
}

