#include "Sweeper.h"

#include "GameBoard.h"

Sweeper::Sweeper(GameBoard* game_board)
	: game_board(game_board)
{
}

Sweeper::SweepingStatus Sweeper::sweep(uint8_t row, uint8_t column)
{
	GameBoard::BoardSquare& square = game_board->get_board_square(row, column);

	if (square.status == GameBoard::MIN)
	{
		square.is_revealed = true;
		emit newSqureRevealed(row, column);
		return EXPLODED;
	}

	check_neighboring(row, column);

	return CLEANED_UP;
}

void Sweeper::check_neighboring(uint8_t row, uint8_t column)
{
	GameBoard::BoardSquare& square = game_board->get_board_square(row, column);

	// Base cases
	if (square.is_revealed || square.neighboring_mine_count > 0)
	{
		square.is_revealed = true;
		emit newSqureRevealed(row, column);
		return;
	}

	square.is_revealed = true;

	emit newSqureRevealed(row, column);

	// If it is clear, check the its neighboring
	int a[3] = {0, -1, 1};

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
		{
			int row_neighboring_position = row - a[i];
			int column_neighboring_position = column - a[j];

			// Prevent from double checking
			if (row_neighboring_position == row && column_neighboring_position == column)
				continue;

			//TODO: Could be wrap into a function named boundary check(remove duplicate code )
			if (row_neighboring_position >= game_board->row ||
					row_neighboring_position < 0)
				continue;
			if (column_neighboring_position >= game_board->column ||
					column_neighboring_position < 0)
				continue;

			check_neighboring(row_neighboring_position, column_neighboring_position);
		}
}
