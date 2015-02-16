import QtQuick 2.3

ColorCell {
	id: colorPicker
	cellColor: "red"
	onClicked: 
		colorColumn.visible = true
	
	signal selected(color colorSelected)
	
	Column {
		id: colorColumn
		visible: false

		function select(colorSelected) {
			colorPicker.cellColor = colorSelected
			colorColumn.visible = false
			colorPicker.selected(colorSelected)
		}
		
		ColorCell { cellColor: "red";    onClicked: colorColumn.select(cellColor) }
		ColorCell { cellColor: "green";  onClicked: colorColumn.select(cellColor) }
		ColorCell { cellColor: "blue";   onClicked: colorColumn.select(cellColor) }
		ColorCell { cellColor: "yellow"; onClicked: colorColumn.select(cellColor) }
	}
}