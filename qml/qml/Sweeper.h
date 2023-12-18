#ifndef SWEEPER_H
#define SWEEPER_H

#include "inttypes.h"

#include <QObject>

class GameBoard;

class Sweeper: public QObject
{
		Q_OBJECT

signals:
	void newSqureRevealed(uint8_t i, uint8_t j);

	public:
		Sweeper(GameBoard* game_board);

        enum SweepingStatus
        {
            EXPLODED,
            CLEANED_UP,
        };

		Q_ENUM(SweepingStatus)

        SweepingStatus sweep(uint8_t i, uint8_t j);
        void check_neighboring(uint8_t row, uint8_t column);

		inline int get_revealed_count() const {
			return revealed_count;
		}
    
        
    private:
		GameBoard* game_board;

		int revealed_count;

};

#endif
