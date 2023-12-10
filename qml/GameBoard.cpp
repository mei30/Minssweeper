#include "GameBoard.h"

#include <random>

GameBoard::GameBoard(uint8_t row, uint8_t column)
{
    grid.reserve(row);

    Grid::iterator iterator = grid.begin();

    // Reserving space for board game in advance
    for (; iterator != grid.end(); ++iterator)
        iterator->reserve(column);
}

GameBoard::BoardSquare& GameBoard::get_board_square(uint8_t row, uint8_t column)
{
    //TODO: For sake of safe coding, Please do a boundary check, and throw damn exception
    return grid[row][column];
}

void GameBoard::place_mins()
{
    // TODO: Make game difficulty configurable
    int mins_count = 1;

    // getting random number something between row - 1 and column(c++ only)
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> row_distribute(0,row - 1);
    std::uniform_int_distribution<std::mt19937::result_type> column_distribute(0,column - 1);
    while (mins_count <= 10)
    {
        uint8_t i = row_distribute(rng);
        uint8_t j = column_distribute(rng);

        // Prevent from placing multiple mins in same place
        if (grid[i][j].status != MIN)
        {
            grid[i][j].status = MIN;
            add_to_neighboring_min_count(i, j);
        }
        else
        {
            mins_count -= 1;
            continue;
        }
    }
}

void GameBoard::add_to_neighboring_min_count(uint8_t row, uint8_t column)
{
    int8_t a[3] = {0, -1,  1};

    // Add to neighboring mins count, if there is any
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
    {
        int row_neighboring_position = row - i;
        int column_neighboring_position = column - j;

        //TODO: Could be wrap into a function named boundary check(remove duplicate code )
        if (row_neighboring_position >= row ||
                row_neighboring_position <= 0)
            continue;
        if (column_neighboring_position >= column ||
                column_neighboring_position <= 0)
            continue;

        ++grid[row_neighboring_position][column_neighboring_position].neighboring_mine_count;
    }
}