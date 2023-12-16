import QtQuick 2.0

import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
	visible: true
	width: 400
	height: 300
	title: "Hover Event Example"

	Rectangle {
		width: 200
		height: 100
		color: "lightblue"

		MouseArea {
			anchors.fill: parent

			// Hover Enter Event
			onEntered: {
				parent.color = "lightgreen";
				console.log("Mouse entered");
			}

			// Hover Exit Event
			onExited: {
				parent.color = "lightblue";
				console.log("Mouse exited");
			}

			// Click Event
			onClicked: {
				console.log("Mouse clicked");
			}
		}

		Text {
			anchors.centerIn: parent
			text: "Hover over me"
		}
	}
}
