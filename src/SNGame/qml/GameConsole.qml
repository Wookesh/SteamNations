import QtQuick 2.3
import SN 1.0
import SNGM 1.0 as SN

Rectangle {
	id: gameConsole
	x: 0
	y: 0
	z: 1000
	color: 'black'
	opacity: 0.6
	width: 400
	height: 300
	
	property SNConsole snConsole;
	
	function createConnections() {
		snConsole = SN.gm.console;
		snConsole.logChanged.connect(display.updateText)
		snConsole.historyChanged.connect(gameConsole.resetHistoryPos)
	}
	
	function resetHistoryPos() {
		input.pos = snConsole.history.length - 1;
	}
	
	TextEdit {
		id: display
		
		property var page: 0;
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.top: parent.top
		color: 'white'
		readOnly: true
		width: parent.width - 2
		height: parent.height - input.height - line.height
		
		function updateText() {
			display.text = '';
			var start = Math.max(0, snConsole.log.length - 18);
			for (var i = start; i < snConsole.log.length; i++) {
				display.text = display.text + snConsole.log[i] + '\n';
			}
		}
		
		function displayPrevious() {
			
		}
	}
	
	Rectangle {
		id: line
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.top: display.bottom
		color: 'white'
		opacity: 1
		width: parent.width - 2
		height: 1
	}
	
	TextInput {
		id: input
		property var pos: 0;
		color: 'white'
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.top: line.bottom
		width: parent.width - 2
		height: font.pixelSize + 10;
		
		Keys.onPressed: {
			if (event.key == Qt.Key_QuoteLeft) {
				gameConsole.visible = !gameConsole.visible;
				event.accepted = true;
				gameUI.focus = true;
			} else if (event.key == Qt.Key_Up) {
				if (input.pos >= 0) {
					input.text = snConsole.history[input.pos]
					--input.pos;
				}
				event.accepted = true;
			} else {
				input.pos = snConsole.history.length - 1;
			}
		}
		
		Keys.onReturnPressed: {
			snConsole.parse(input.text);
			input.text = '';
			event.accepted = true;
		}
	}
	
	function getFocus() {
		input.focus = true;
	}
}