import QtQuick 2.12
import QtQuick.Window 2.12

import QtQuick.Layouts 1.3

// Finding a way for positioning
// Adding game states(loose, win)
// Adding animation

// Fixme: A lot of const numbers that kill flexibility(more knowldege of posiitioning is needed)
Window {
	id: root

	visible: true
	property int margin: 5
	property int row: 10
	property int column: 10
	property int square_size: 50
	property int column_spacing: 5
	property int row_spacing: 5
	property int socreboard_height_size: 50

	minimumWidth: square_size * row + (row - 1) * row_spacing  + margin * 2
	minimumHeight: square_size * column + (column - 1) * column_spacing + 10 + socreboard_height_size + margin * 2

	maximumWidth: square_size * row + (row - 1) * row_spacing  + margin * 2
	maximumHeight: square_size * column + (column - 1) * column_spacing + 10 + socreboard_height_size + margin * 2

	title: "Minsweeper"

	ColumnLayout {
		id: mainlayout
		anchors.fill: parent
		anchors.margins: margin
		spacing: 10

		ScoreBoard {
			Layout.fillWidth: true
		}

		GameBoard {
			Layout.fillHeight: true
			Layout.fillWidth: true
		}
	}
}

