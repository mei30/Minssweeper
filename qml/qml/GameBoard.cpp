#include "GameBoard.h"

#include <random>

#include <QDebug>

void GameBoard::data_changed(uint8_t i, uint8_t j)
{
	QModelIndex index = this->index(i, j);
	emit dataChanged(index, index,  QVector<int>() << Is_REVEALED);
}

int GameBoard::sweep(int i, int j)
{
	return sweeper.sweep(i, j);
}

void GameBoard::reveal_mins()
{
	for_each(mins.begin(), mins.end(), [this](std::pair<int, int>& min) {
		this->grid[min.first][min.second].is_revealed = true;
		data_changed(min.first, min.second);
	});
}

int GameBoard::get_revealed_count()
{
	return sweeper.get_revealed_count();
}

GameBoard::GameBoard(QObject *parent)
	: QAbstractTableModel(parent)
	, row(10)
	, column(10)
	, grid(row, std::vector<BoardSquare>(column, BoardSquare{}))
	, sweeper(this)
	, revealed_count(0)
{
	connect(&sweeper, &Sweeper::newSqureRevealed, this, &GameBoard::data_changed);

	this->place_mins();
}

GameBoard::BoardSquare& GameBoard::get_board_square(uint8_t row, uint8_t column)
{
	//TODO: For sake of safe coding, Please do a boundary check, and throw damn exception
	return grid[row][column];
}

int GameBoard::rowCount(const QModelIndex& index) const
{
	if (index.isValid())
		return 0;

	return row;
}

int GameBoard::columnCount(const QModelIndex& index) const
{
	if (index.isValid())
		return 0;

	return column;
}

QVariant GameBoard::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	BoardSquare board_square = this->grid[index.row()][index.column()];

	switch (role) {
		case STATUS:
			return QVariant(board_square.status);
		case Is_REVEALED:
			return QVariant(board_square.is_revealed);
		case NEIGHBORING_MINE_COUNT:
			return QVariant(board_square.neighboring_mine_count);
	default:
		break;
	}

	return QVariant();
}

QVariant GameBoard::headerData(int section, Qt::Orientation orientation, int role) const
{
	return QVariant();
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
			mins.push_back({i, j});
			add_to_neighboring_min_count(i, j);
		}
		else
		{
			mins_count -= 1;
			continue;
		}

		++mins_count;
	}
}

void GameBoard::add_to_neighboring_min_count(uint8_t row, uint8_t column)
{
	int8_t a[3] = {0, -1,  1};

	// Add to neighboring mins count, if there is any
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
		{
			int row_neighboring_position = row - a[i];
			int column_neighboring_position = column - a[j];

			//TODO: Could be wrap into a function named boundary check(remove duplicate code )
			if (row_neighboring_position >= this->row ||
					row_neighboring_position < 0)
				continue;
			if (column_neighboring_position >= this->column ||
					column_neighboring_position < 0)
				continue;

			++grid[row_neighboring_position][column_neighboring_position].neighboring_mine_count;
		}
}
