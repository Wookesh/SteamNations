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
}

