import QtQuick 2.0

import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Rectangle {
	id: square
	property int status: SquareStatus.CLEAR
	property bool revealed : false
	property int neighboring_mine_count: 0
	property real w: 50
	property real h: 50

	implicitHeight: h
	implicitWidth: w

	width: w
	height: h
	color: "#F97B22"
	radius: 8

	layer.enabled: true
	layer.effect:  DropShadow {
			verticalOffset: 4
			radius: 8.0
			samples: 17
			color: "#b0000000"
		}
}
