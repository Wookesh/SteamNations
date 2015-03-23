import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

TextButton {
	id: textButton
	
	source: "qrc:///textButton"
	
	function check() {
		background.visible = true;
	}
	
	function uncheck() {
		background.visible = false;
	}
	
	Image {
		id: background
		source: "qrc:///textButtonShadow3"
		z: -1
		visible: false
		width: parent.width
		height: parent.height
	}
}
