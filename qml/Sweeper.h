#ifndef SWEEPER_H
#define SWEEPER_H

#include "inttypes.h"

class GameBoard;

class Sweeper
{
    public:
        Sweeper(GameBoard& game_board);

        enum SweepingStatus
        {
            EXPLODED,
            CLEANED_UP,
        };

        SweepingStatus sweep(uint8_t i, uint8_t j);
        void check_neighboring(uint8_t row, uint8_t column);
    
        
    private:
        GameBoard& game_board;

};

#endif