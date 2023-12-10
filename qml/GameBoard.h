#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <vector>
#include <inttypes.h>

class GameBoard
{
    public:
        enum SquareStatus
        {
            MIN,
            CLEAR
        };

        struct BoardSquare
        {
            BoardSquare()
            : status(CLEAR)
            , is_revealed(false)
            , sign('#')
            , neighboring_mine_count(0)
            {
            }

            SquareStatus status;
            bool is_revealed;
            char sign;
            uint8_t neighboring_mine_count;
        };

        GameBoard(uint8_t row, uint8_t column);

        BoardSquare& get_board_square(uint8_t row, uint8_t column);

    private:
        typedef std::vector<std::vector<BoardSquare>> Grid;

        void place_mins();
        void add_to_neighboring_min_count(uint8_t i, uint8_t j);

        Grid grid;

        uint8_t row;
        uint8_t column;
};

#endif