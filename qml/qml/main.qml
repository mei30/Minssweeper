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
		color: "#edede9"

		TableView {
			id: tableview
			property int counter: -1

			anchors.fill: parent
			anchors.leftMargin: 5
			anchors.rightMargin: 5
			anchors.topMargin: 5
			anchors.bottomMargin: 5
			columnSpacing: 5
			rowSpacing: 5
			clip: true


			model: GameBoard {
				id: board
			}

			delegate: Square {

				id: square

				w: Math.floor((root.width - 45 - 10) / 10)
				h: Math.floor((root.height - 45 - 10) / 10)
				i: tableview.i
				j: tableview.j
				status: model.status
				revealed: model.revealed
				neighboring_mine_count: model.neighboring_mine_count

				onSquareClicked: (i, j) => {

					console.log("on square clicked", i, j)
					board.sweep(i, j)
				}

				Component.onCompleted: {
					++tableview.counter;

					square.i = Math.floor(tableview.counter / 10)
					square.j = tableview.counter % 10
				}
			}
		}
	}
}

