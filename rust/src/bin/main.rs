use minssweeper::MinsSweeper;

// Future Improvements
// Add a beautiful graphical ui for game
// Separate each part into conceptual modules
// Apply rust patterns as much as possible
fn main() {
    let mut game = MinsSweeper::new(10, 10);

    game.start();
}
