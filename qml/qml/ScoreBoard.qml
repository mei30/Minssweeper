import QtQuick 2.0

Item {
	id: scoreboard

	height: root.socreboard_height_size

	Image {
		id: closebutton

		source: "qrc:/assets/images/icons8-cancel-50.png"

		sourceSize.width: 36
		sourceSize.height: 36

		MouseArea {
			anchors.fill: parent
			hoverEnabled: true
			onClicked: {
				console.log("Clicked")
			}

			onEntered: {
				console.log("Entered")
				closebutton.width = closebutton.sourceSize.width + 2
				closebutton.height = closebutton.sourceSize.height + 2
			}

			onExited: {
				closebutton.width = closebutton.sourceSize.width - 2
				closebutton.height = closebutton.sourceSize.height - 2
			}
		}
	}

	Rectangle {
		anchors.horizontalCenter: parent.horizontalCenter
		height: 50
		width: 300

		Image {
			id: emoji
			source: "qrc:/assets/images/icons8-happy-50.png"
			anchors.leftMargin: 20
			anchors.horizontalCenter: parent.horizontalCenter
		}

		Rectangle {
			anchors.left: parent.left
			anchors.verticalCenter: parent.verticalCenter
			width: 100
			height: 40
			radius: 50
			border.color: "black"

			Image {
				id: flagicon
				source: "qrc:/assets/images/icons8-triangular-flag-48.png"
				anchors.verticalCenter: parent.verticalCenter
				anchors.left: parent.left
				anchors.leftMargin: 10

				sourceSize.width: 28
				sourceSize.height: 28
			}

			Text {
				id: flagnumber
				anchors.rightMargin: 10
				anchors.right: parent.right
				anchors.verticalCenter: parent.verticalCenter
				text: qsTr("5")
				color: "#73777B"
				font.pointSize: 20
				font.family: "arial"
			}
		}

		Rectangle {
			anchors.right: parent.right
			anchors.verticalCenter: parent.verticalCenter
			width: 100
			height: 40
			radius: 50
			border.color: "black"

			Image {
				id: timeicon
				source: "qrc:/assets/images/icons8-clock-50.png"
				anchors.verticalCenter: parent.verticalCenter
				anchors.left: parent.left
				anchors.leftMargin: 10

				sourceSize.width: 28
				sourceSize.height: 28
			}

			Text {
				id: time
				anchors.rightMargin: 10
				anchors.right: parent.right
				anchors.verticalCenter: parent.verticalCenter
				text: qsTr("1:5")
				color: "#73777B"
				font.pointSize: 20
				font.family: "arial"
			}
		}

//		Item {
//			anchors.left: emoji.right

//			Image {
//				id: timeicon
//				source: "qrc:/assets/images/icons8-clock-50.png"

//				sourceSize.width: 25
//				sourceSize.height: 25
//			}

//			Text {
//				id: time
//				text: qsTr("1:5")
//				color: gray
//			}
//		}
	}
}
