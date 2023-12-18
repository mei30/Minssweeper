import QtQuick 2.12
import QtQuick.Layouts 1.3

import Min 1.0

TableView {
	id: tableview
	property int counter: -1
	property bool lost: false
	property bool win: false
	property int explosion: SweepingStatus.EXPLODED

	signal explosionhappend
	signal winhappend
	signal lucky

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
							 if (tableview.lost)
							 return;

							 if (win)
								return;

							 var revealed_count = board.get_revealed_count()
							 console.log(revealed_count)

							 if (revealed_count === 90) {
								 win = true
								 tableview.winhappend()
								 return
							 }

							 var result = board.sweep(i, j)

							 if (result !== tableview.explosion)
							 {
								tableview.lucky()
								return;
							 }

							tableview.lost = true
							board.reveal_mins();

							tableview.explosionhappend()

						 }

		Component.onCompleted: {
			++tableview.counter;


			square.i = Math.floor(tableview.counter / 10)
			square.j = tableview.counter % 10
			console.log(square.i, square.j)
		}
	}
}
