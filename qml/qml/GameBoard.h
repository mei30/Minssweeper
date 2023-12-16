#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <vector>
#include <inttypes.h>

#include <QObject>
#include <QAbstractTableModel>

#include "Sweeper.h"


class GameBoard : public QAbstractTableModel
{
	Q_OBJECT


public slots:
	void data_changed(uint8_t i, uint8_t j);

public:

	enum
	{
		STATUS = Qt::UserRole,
		Is_REVEALED,
		NEIGHBORING_MINE_COUNT
	};

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
			, neighboring_mine_count(0)
		{
		}

		SquareStatus status;
		bool is_revealed;
		uint8_t neighboring_mine_count;
	};
	Q_ENUM(SquareStatus)

	typedef std::vector<std::vector<BoardSquare>> Grid;

	Q_INVOKABLE int sweep(int i, int j);


	GameBoard(QObject *parent = nullptr);

	BoardSquare& get_board_square(uint8_t row, uint8_t column);

	inline Grid get_grid()
	{
		return grid;
	}

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	inline QHash<int, QByteArray> roleNames() const override {
		return {
			{ {STATUS, "status"},
			  {Is_REVEALED, "revealed"},
			  {NEIGHBORING_MINE_COUNT, "neighboring_mine_count"}
			}
		};
	}

	uint8_t row;
	uint8_t column;

private:
	void place_mins();
	void add_to_neighboring_min_count(uint8_t i, uint8_t j);

	Grid grid;

	Sweeper sweeper;

};

#endif
