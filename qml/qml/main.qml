import QtQuick 2.12
import QtQuick.Window 2.12

import QtQuick.Layouts 1.3

import Min 1.0

import QtGraphicalEffects 1.0

Window {
	id: root
	width: 640
	height: 640
	visible: true
	title: "Minsweeper"

	Rectangle {
		anchors.fill: parent
		color: "#FEE8B0"

		TableView {
			anchors.fill: parent
			anchors.leftMargin: 5
			anchors.rightMargin: 5
			anchors.topMargin: 5
			anchors.bottomMargin: 5
			columnSpacing: 5
			rowSpacing: 5
			clip: true


			model: GameBoard {}

			delegate:  Square {
				id: sh
				w: Math.floor((root.width - 45 - 10) / 10)
				h: Math.floor((root.height - 45 - 10) / 10)
				status: model.status
				revealed: model.revealed
				neighboring_mine_count: model.neighboring_mine_count

				}

	}
	}

}

