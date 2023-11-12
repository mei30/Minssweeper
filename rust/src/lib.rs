use rand::Rng;

use std::io;

fn add(u: usize, i: i32) -> Option<usize> {
    if i.is_negative() {
        u.checked_sub(i.wrapping_abs() as u32 as usize)
    } else {
        u.checked_add(i as usize)
    }
}

// Temporarily public
#[derive(Clone)]
enum SquareStatus {
    MIN,
    CLEAR(u16),
}

#[derive(Clone)]
struct BoardSquare {
    status: SquareStatus,
    is_revealed: bool,
    sign: char,
}
struct Board {
    grid: Vec<Vec<BoardSquare>>,
    row: usize,
    column: usize,
}

impl Board {
    fn new(row: usize, column: usize) -> Board {
        let mut grid: Vec<Vec<BoardSquare>> = Vec::with_capacity(row);

        for _ in 0..grid.capacity() {
            grid.push(vec![
                BoardSquare {
                    status: SquareStatus::CLEAR(0),
                    is_revealed: false,
                    sign: '-'
                };
                column
            ]);
        }

        Board { grid, row, column }
    }

    fn init(&mut self) {
        self.place_mines();
        self.count_neighboring_mines();
        self.display();
    }

    fn get_square(&mut self, row: usize, column: usize) -> &mut BoardSquare {
        &mut self.grid[row][column]
    }

    fn place_mines(&mut self) {
        let mut rng = rand::thread_rng();

        let mut i = 0;

        // TODO: Number of mins should be configurable
        while i < 10 {
            i += 1;

            let row = rng.gen_range(0..self.row);
            let column = rng.gen_range(0..self.column);

            let board_square = &mut self.grid[row][column];

            match board_square.status {
                SquareStatus::MIN => {
                    i -= 1;
                    continue;
                }
                SquareStatus::CLEAR(_) => {
                    *board_square = BoardSquare {
                        status: SquareStatus::MIN,
                        is_revealed: false,
                        sign: '*',
                    }
                }
            }
        }
    }

    fn count_neighboring_mines(&mut self) {
        for i in 0..self.row {
            for j in 0..self.column {
                if let SquareStatus::CLEAR(_) = self.grid[i][j].status {
                    let mut min_count = 0;

                    let a: [i32; 3] = [-1, 0, 1];

                    for dr in a {
                        for dc in a {
                            let r = add(i, dr);
                            let c = add(j, dc);

                            if let None = r {
                                continue;
                            }

                            if let None = c {
                                continue;
                            }

                            let r = r.unwrap();
                            let c = c.unwrap();

                            if (r < self.row) && (c < self.column) {
                                min_count += if let SquareStatus::MIN = self.grid[r][c].status {
                                    1
                                } else {
                                    0
                                };
                            }
                        }
                    }

                    self.grid[i][j] = BoardSquare {
                        status: SquareStatus::CLEAR(min_count),
                        is_revealed: false,
                        sign: char::from_digit(min_count as u32, 10).unwrap(),
                    }
                }
            }
        }
    }

    fn display(&self) {
        clearscreen::clear().expect("failed to clear screen");

        print!("  ");
        for i in 0..self.row {
            print!("{} ", i);
        }
        print!("\n");
        for i in 0..self.row {
            print!("{} ", i);
            for j in 0..self.column {
                let sign = if self.grid[i][j].is_revealed {
                    self.grid[i][j].sign
                } else {
                    '#'
                };
                print!("{} ", sign);
            }
            println!("\n");
        }
    }
}

struct Sweeper {
    board: Board,
}

impl Sweeper {
    fn sweep(&mut self, row: usize, column: usize) -> bool {
        let square = self.board.get_square(row, column);

        if square.is_revealed {
            return true;
        }

        square.is_revealed = true;

        match square.status {
            SquareStatus::CLEAR(count) => {
                if count > 0 {
                    println!("count {}", count);
                    return true;
                }

                let a: [i32; 3] = [-1, 0, 1];

                for dr in a {
                    for dc in a {
                        let r = add(row, dr);
                        let c = add(column, dc);

                        if let None = r {
                            continue;
                        }

                        if let None = c {
                            continue;
                        }

                        let r = r.unwrap();
                        let c = c.unwrap();

                        if (r < self.board.row) && (c < self.board.column) {
                            self.sweep(r, c);
                        }
                    }
                }
                return true;
            }

            SquareStatus::MIN => {
                return false;
            }
        }
    }
}

pub struct MinsSweeper {
    sweeper: Sweeper,
}

impl MinsSweeper {
    pub fn new(row: usize, column: usize) -> MinsSweeper {
        let board = Board::new(row, column);

        println!("10X10 MinsSweeper Game\n");

        MinsSweeper {
            sweeper: Sweeper { board },
        }
    }

    pub fn start(&mut self) {
        self.sweeper.board.init();

        loop {
            let mut line = String::new();

            io::stdin()
                .read_line(&mut line)
                .expect("Failed to read line");

            println!("{:?}", line.split(" "));

            let inputs: Vec<usize> = line
                .split_whitespace()
                .map(|x| x.parse().expect("Not an integer!"))
                .collect();

            let result = self.sweeper.sweep(inputs[0], inputs[1]);

            if !result {
                println!("You failed!");
                break;
            }

            self.sweeper.board.display();
        }
    }
}
