import QtQuick 2.0

Rectangle {
	width: 50
	height: 50
	color: "#C0CBC6"
	radius: 3

	MouseArea {
		anchors.fill: parent
		onClicked: console.log("Hello from Squre")
	}
}
