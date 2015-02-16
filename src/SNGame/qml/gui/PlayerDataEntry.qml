import QtQuick 2.3
import QtQuick.Controls 1.2
import "./colorPicker"

Item {
	id: entry
	Row {
		TextField {
			id: nameBox
		}
		ColorPicker {
			id: colorPicker
		}
	}
}