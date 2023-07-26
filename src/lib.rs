// Temporarily public

use std::fmt::DebugStruct;

#[derive(Clone)]
enum SquareStatus {
    BOMB,
    CLEAR(u16),
}

#[derive(Clone)]
struct BoardSquare {
    square_status: SquareStatus,
    is_revealed: bool,
    sign: char,
}
pub struct Board {
    grid: Vec<Vec<BoardSquare>>,
}

impl Board {
    pub fn new(row: usize, column: usize) -> Board {
        let mut grid: Vec<Vec<BoardSquare>> = Vec::with_capacity(row);

        for i in grid.iter_mut() {
            *i = vec![
                BoardSquare {
                    square_status: SquareStatus::CLEAR(0),
                    is_revealed: false,
                    sign: '#'
                };
                column
            ]
        }

        Board { grid }
    }

    fn get_ith_square()
}

pub struct Sweeper {
    board: Board,
}

pub struct MinsSweeper {
    sweeper: Sweeper,
}

impl MinsSweeper {
    fn new(row: usize, column: usize) -> MinsSweeper {
        let board = Board::new(row, column);

        MinsSweeper {
            sweeper: Sweeper { board },
        }
    }
}
