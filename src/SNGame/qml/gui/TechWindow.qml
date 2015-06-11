import QtQuick 2.3
import QtQuick.Controls 1.2
import SN 1.0

SNImage {

	id:techWindow
	property BonusManager snBonusManager;
	property var owner : "undefined"
	property var name  : "undefined"
	property var nameBoxHeight : 180 * root.globalScale.height
	property var boxWidth: 220 * root.globalScale.width
	property var imageSizeH: 80 * root.globalScale.height
	property var imageSizeW: 80 * root.globalScale.width
	property var labelWidth:imageSizeW*3/2
	property var startingWidth: -(techWindow.width - 3 * imageSizeW) / 8
	property var labelDist:2
	property var applied:"green"
	property var affordable: "yellow"
	property var unaffordable:"red"
	
	visible: false
	source: "qrc:///techWindow"
	
	MouseArea {
		anchors.fill: parent
	}
	
	function bonusesUpdated() {
		if(snBonusManager.isApplied(0))
			defence1.border.color = applied;
		else if (snBonusManager.isAffordable(0))
			defence1.border.color = affordable;
		else
			defence1.border.color = unaffordable;
		
		if(snBonusManager.isApplied(1))
			defence2.border.color = applied;
		else if (snBonusManager.isAffordable(1))
			defence2.border.color = affordable;
		else
			defence2.border.color = unaffordable;
		
		if(snBonusManager.isApplied(2))
			defence3.border.color = applied;
		else if (snBonusManager.isAffordable(2))
			defence3.border.color = affordable;
		else
			defence3.border.color = unaffordable;
		
		if(snBonusManager.isApplied(3))
			warfare1.border.color = applied;
		else if (snBonusManager.isAffordable(3))
			warfare1.border.color = affordable;
		else
			warfare1.border.color = unaffordable;
		
		if(snBonusManager.isApplied(4))
			warfare2.border.color = applied;
		else if (snBonusManager.isAffordable(4))
			warfare2.border.color = affordable;
		else
			warfare2.border.color = unaffordable;
		
		if(snBonusManager.isApplied(5))
			warfare3.border.color = applied;
		else if (snBonusManager.isAffordable(5))
			warfare3.border.color = affordable;
		else
			warfare3.border.color = unaffordable;
		
		if(snBonusManager.isApplied(6))
			economy1.border.color = applied;
		else if (snBonusManager.isAffordable(6))
			economy1.border.color = affordable;
		else
			economy1.border.color = unaffordable;
		
		if(snBonusManager.isApplied(7))
			economy2.border.color = applied;
		else if (snBonusManager.isAffordable(7))
			economy2.border.color = affordable;
		else
			economy2.border.color = unaffordable;
		
		if(snBonusManager.isApplied(8))
			economy3.border.color = applied;
		else if (snBonusManager.isAffordable(8))
			economy3.border.color = affordable;
		else
			economy3.border.color = unaffordable;
		
	}
	
	function createConnections() {
		snBonusManager = scene.bonusManager;
		snBonusManager.bonusesUpdated.connect(techWindow.bonusesUpdated);
	}
	
	Rectangle{
		id:defence1
		width:imageSizeW 
		height:imageSizeH
		color:"#2770C3"
		border.color:unaffordable
		border.width:5
		x: startingWidth + (parent.width - 3 * imageSizeW) / 4
		y: 2*(parent.height - 3 * imageSizeH) / 4
		MenuButton {
			source:"qrc:///icon/Damage";
			onClicked:snBonusManager.tryToApplyBonus(0);
			Label {
				text:"1"
				x:parent.width-this.width
				y:parent.height-this.height
				font.family: snFont.name
				font.pixelSize: 32
				color: "white"
			}
		}
	}
	Label{
        wrapMode: Text.WordWrap
		width:labelWidth
		x: startingWidth + labelDist  + (parent.width - 3 * imageSizeW) / 4 + imageSizeW
		y: 2*(parent.height - 3 * imageSizeH) / 4
		text: snBonusManager.desc(0)
        font.pixelSize: 11
	}
	
	Rectangle{
		id:defence2
		width:imageSizeW 
		height:imageSizeH 
		color:"#2770C3"
		border.color:unaffordable
		border.width:5
		x: startingWidth + 2*(parent.width - 3 * imageSizeW) / 4 + imageSizeW
		y: 2*(parent.height - 3 * imageSizeH) / 4
		MenuButton {
			source:"qrc:///icon/Damage";
			onClicked:snBonusManager.tryToApplyBonus(1);
			Label {
				text:"2"
				x:parent.width-this.width
				y:parent.height-this.height
				font.family: snFont.name
				font.pixelSize: 32
				color: "white"
			}
		}
	}
	Label{
        wrapMode: Text.WordWrap
		width:labelWidth
		x: startingWidth + labelDist  + 2*(parent.width - 3 * imageSizeW) / 4 + 2*imageSizeW
		y: 2*(parent.height - 3 * imageSizeH) / 4
		text: snBonusManager.desc(1)
        font.pixelSize: 11
	}
	
	Rectangle{
		id:defence3
		width:imageSizeW 
		height:imageSizeH 
		color:"#2770C3"
		border.color:unaffordable
		border.width:5
		x: startingWidth + 3*(parent.width - 3 * imageSizeW) / 4 + 2*imageSizeW
		y: 2*(parent.height - 3 * imageSizeH) / 4
		MenuButton {
			source:"qrc:///icon/Damage";
			onClicked:snBonusManager.tryToApplyBonus(2);
			Label {
				text:"3"
				x:parent.width-this.width
				y:parent.height-this.height
				font.family: snFont.name
				font.pixelSize: 32
				color: "white"
			}
		}
	}
	Label{
        wrapMode: Text.WordWrap
		width:labelWidth
		x: startingWidth + labelDist  + 3*(parent.width - 3 * imageSizeW) / 4 + 3*imageSizeW
		y: 2*(parent.height - 3 * imageSizeH) / 4
		text: snBonusManager.desc(2)
        font.pixelSize: 11
	}
	
	Rectangle{
		id:warfare1
		width:imageSizeW 
		height:imageSizeH 
		color:"#aa2525"
		border.color:unaffordable
		border.width:5
		x: startingWidth + (parent.width - 3 * imageSizeW) / 4
		y: 3*(parent.height - 3 * imageSizeH) / 4 + imageSizeH/2
		MenuButton {
			source:"qrc:///icon/Attack";
			onClicked:snBonusManager.tryToApplyBonus(3);
			Label {
				text:"1"
				x:parent.width-this.width
				y:parent.height-this.height
				font.family: snFont.name
				font.pixelSize: 32
				color: "white"
			}
		}
	}
	Label{
        wrapMode: Text.WordWrap
		width:labelWidth
		x: startingWidth + labelDist  + (parent.width - 3 * imageSizeW) / 4 + imageSizeW
		y: 3*(parent.height - 3 * imageSizeH) / 4 + imageSizeH/2
		text: snBonusManager.desc(3)
        font.pixelSize: 11
	}
	
	Rectangle{
		id:warfare2
		width:imageSizeW 
		height:imageSizeH 
		color:"#aa2525"
		border.color:unaffordable
		border.width:5
		x: startingWidth + 2*(parent.width - 3 * imageSizeW) / 4 + imageSizeW
		y: 3*(parent.height - 3 * imageSizeH) / 4 + imageSizeH/2
		MenuButton {
			source:"qrc:///icon/Attack";
			onClicked:snBonusManager.tryToApplyBonus(4);
			Label {
				text:"2"
				x:parent.width-this.width
				y:parent.height-this.height
				font.family: snFont.name
				font.pixelSize: 32
				color: "white"
			}
		}
	}
	Label{
        wrapMode: Text.WordWrap
		width:labelWidth
		x: startingWidth + labelDist  + 2*(parent.width - 3 * imageSizeW) / 4 + 2*imageSizeW
		y: 3*(parent.height - 3 * imageSizeH) / 4 + imageSizeH/2
		text: snBonusManager.desc(4)
        font.pixelSize: 11
	}
	
	Rectangle{
		id:warfare3
		width:imageSizeW 
		height:imageSizeH 
		color:"#aa2525"
		border.color:unaffordable
		border.width:5
		x: startingWidth + 3*(parent.width - 3 * imageSizeW) / 4 + 2*imageSizeW
		y: 3*(parent.height - 3 * imageSizeH) / 4 + imageSizeH/2
		MenuButton {
			source:"qrc:///icon/Attack";
			onClicked:snBonusManager.tryToApplyBonus(5);
			Label {
				text:"3"
				x:parent.width-this.width
				y:parent.height-this.height
				font.family: snFont.name
				font.pixelSize: 32
				color: "white"
			}
		}
	}
	Label{
        wrapMode: Text.WordWrap
		width:labelWidth
		x: startingWidth + labelDist  + 3*(parent.width - 3 * imageSizeW) / 4 + 3*imageSizeW
		y: 3*(parent.height - 3 * imageSizeH) / 4 + imageSizeH/2
		text: snBonusManager.desc(5)
        font.pixelSize: 11
	}
	
	Rectangle{
		id:economy1
		width:imageSizeW
		height:imageSizeH 
		color:"#2ECA48"
		border.color:unaffordable
		border.width:5
		x: startingWidth + (parent.width - 3 * imageSizeW) / 4
		y: 4*(parent.height - 3 * imageSizeH) / 4 + imageSizeH
		MenuButton {
			source:"qrc:///icon/Population";
			onClicked:snBonusManager.tryToApplyBonus(6);
			Label {
				text:"1"
				x:parent.width-this.width
				y:parent.height-this.height
				font.family: snFont.name
				font.pixelSize: 32
				color: "white"
			}
		}
	}
	Label{
        wrapMode: Text.WordWrap
		width:labelWidth
		x: startingWidth + labelDist  + (parent.width - 3 * imageSizeW) / 4 + imageSizeW
		y: 4*(parent.height - 3 * imageSizeH) / 4 + imageSizeH
		text: snBonusManager.desc(6)
        font.pixelSize: 11
	}
	
	Rectangle{
		id:economy2
		width:imageSizeW 
		height:imageSizeH 
		color:"#2ECA48"
		border.color:unaffordable
		border.width:5
		x: startingWidth + 2*(parent.width - 3 * imageSizeW) / 4 + imageSizeW
		y: 4*(parent.height - 3 * imageSizeH) / 4 + imageSizeH
		MenuButton {
			source:"qrc:///icon/Population";
			onClicked:snBonusManager.tryToApplyBonus(7);
			Label {
				text:"2"
				x:parent.width-this.width
				y:parent.height-this.height
				font.family: snFont.name
				font.pixelSize: 32
				color: "white"
			}
		}
	}
	Label{
        wrapMode: Text.WordWrap
		width:labelWidth
		x: startingWidth + labelDist  + 2*(parent.width - 3 * imageSizeW) / 4 + 2*imageSizeW
		y: 4*(parent.height - 3 * imageSizeH) / 4 + imageSizeH
		text: snBonusManager.desc(7)
        font.pixelSize: 11
	}
	
	Rectangle{
		id:economy3
		width:imageSizeW 
		height:imageSizeH
		color:"#2ECA48"
		border.color:unaffordable
		border.width:5
		x: startingWidth + 3*(parent.width - 3 * imageSizeW) / 4 +2*imageSizeW
		y: 4*(parent.height - 3 * imageSizeH) / 4 + imageSizeH
		MenuButton {
			source:"qrc:///icon/Population";
			onClicked:snBonusManager.tryToApplyBonus(8);
			Label {
				text:"3"
				x:parent.width-this.width
				y:parent.height-this.height
				font.family: snFont.name
				font.pixelSize: 32
				color: "white"
			}
		}
	}
	Label{
        wrapMode: Text.WordWrap
		width:labelWidth
		x: startingWidth + labelDist  + 3*(parent.width - 3 * imageSizeW) / 4 + 3*imageSizeW
		y: 4*(parent.height - 3 * imageSizeH) / 4 + imageSizeH
		text: snBonusManager.desc(8)
        font.pixelSize: 11
	}
	
	
	
	
}

