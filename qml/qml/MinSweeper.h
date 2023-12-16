#ifndef MIN_SWEEPER_H
#define MIN_SWEEPER_H

#include "GameBoard.h"
#include "Sweeper.h"

#include <QObject>

// Supposed to work with qml
class MinSweeper: public QObject
{
	Q_OBJECT

    public:
        // TODO: Also get game difficulty 
		MinSweeper(GameBoard *board);

    // public apis for delegating qml events to Sweeper

    private:
		GameBoard *board;
        Sweeper sweeper;
};

#endif

