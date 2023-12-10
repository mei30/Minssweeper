#include "MinSweeper.h"

MinSweeper::MinSweeper(uint8_t row, uint8_t column)
: board(row, column)
, sweeper(board)
{
}