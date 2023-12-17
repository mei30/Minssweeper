import QtQuick 2.12
import QtQuick.Layouts 1.3

import Min 1.0

TableView {
	id: tableview
	property int counter: -1

	columnSpacing: 5
	rowSpacing: 5
	clip: true


	model: GameModelBoard {
		id: board
	}

	delegate: Square {

		id: square

		// Fixme: should be flexible(more knowldege in qml is needed)
		w: root.square_size
		h: root.square_size
		i: tableview.i
		j: tableview.j
		status: model.status
		revealed: model.revealed
		neighboring_mine_count: model.neighboring_mine_count

		onSquareClicked: (i, j) => {

							 console.log(tableview.width, tableview.height)
							 console.log("IMPLICT TABLE", tableview.implicitWidth, tableview.implicitHeight)
							 console.log("IMPLICT SQUARE", square.implicitWidth, square.implicitHeight)
							 console.log(tableview.contentHeight, tableview.contentWidth)

							 console.log("on square clicked", i, j)
							 board.sweep(i, j)
						 }

		Component.onCompleted: {
			++tableview.counter;


			square.i = Math.floor(tableview.counter / 10)
			square.j = tableview.counter % 10
			console.log(square.i, square.j)
		}
	}
}
