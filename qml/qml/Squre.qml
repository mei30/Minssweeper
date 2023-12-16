import QtQuick 2.0

Rectangle {
	id: square
	width: 50
	height: 50
	color: "#C0CBC6"
	radius: 3

	MouseArea {
		hoverEnabled: true
		anchors.fill: parent
		onClicked: console.log("Hello from Squre")

		onEntered: {
						parent.color = "lightgreen";
						console.log("Mouse entered");
					}
	}
}
