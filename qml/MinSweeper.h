#ifndef MIN_SWEEPER
#define MIN_SWEEPER_H

#include "GameBoard.h"
#include "Sweeper.h"

// Supposed to work with qml
class MinSweeper
{
    public:
        // TODO: Also get game difficulty 
        MinSweeper(uint8_t row, uint8_t column);

    // public apis for delegating qml events to Sweeper

    private:
        GameBoard board;
        Sweeper sweeper;
};

#endif

