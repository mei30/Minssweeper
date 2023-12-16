import QtQuick 2.0

import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Image {
	id: root

	signal squareClicked(int i, int j)

	property int status: SquareStatus.CLEAR
	property bool revealed : false
	property int neighboring_mine_count: 0
	property real w: 50
	property real h: 50
	property int i: 0
	property int j: 0

	width: w
	height: h

	sourceSize.width: w
	sourceSize.height: h

	source: get_iamge_based_on_square_condition()

	function get_iamge_based_on_square_condition()
	{
		if (!root.revealed)
			return "qrc:/assets/images/unknown_1_128x128.png"

		if (root.status == 0)
			return "qrc:/assets/images/bomb_128x128.png"

		if (root.neighboring_mine_count == 0)
			return "qrc:/assets/images/empty_128x128.png"
		if (root.neighboring_mine_count == 1)
			return "qrc:/assets/images/1_128x128.png"
		if (root.neighboring_mine_count == 2)
			return "qrc:/assets/images/2_128x128.png"
		if (root.neighboring_mine_count == 3)
			return "qrc:/assets/images/3_128x128.png"
		if (root.neighboring_mine_count == 4)
			return "qrc:/assets/images/4_128x128.png"
		if (root.neighboring_mine_count == 5)
			return "qrc:/assets/images/5_128x128.png"
		if (root.neighboring_mine_count == 6)
			return "qrc:/assets/images/6_128x128.png"
		if (root.neighboring_mine_count == 7)
			return "qrc:/assets/images/7_128x128.png"
	}

	MouseArea {
		anchors.fill: parent
		onClicked: {
			root.squareClicked(parent.i, parent.j)
		}
	}
}
