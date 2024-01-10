Minesweeper Game
Minesweeper is a classic single-player puzzle game where the objective is to clear a rectangular board containing hidden mines without detonating any of them.

Features
Three difficulty levels: Beginner, Intermediate, and Advanced.
Customizable grid size and number of mines.
Colorful console-based user interface.
Mines are randomly placed on the board.
Player can reveal cells, mark potential mine locations, and win by revealing all safe cells.
User-friendly input for making moves.
How to Play
Choose the difficulty level (Beginner, Intermediate, or Advanced).
The game board will be displayed with cells hidden.
Enter your move by providing the row and column coordinates.
Avoid revealing a mine; otherwise, the game is over.
Continue making moves until you clear all safe cells or hit a mine.
Setup and Compilation
Ensure you have a C++ compiler installed on your system. Compile the code using the following commands:

bash
Copy code
g++ -o minesweeper minesweeper.cpp
Run the compiled executable:

bash
Copy code
./minesweeper
Controls
Use the arrow keys to navigate the cursor.
Enter row and column coordinates to make a move.
Requirements
C++ compiler
Windows operating system (for console color manipulation)
Customization
You can customize the game grid size and number of mines by modifying the choosedifficulty function in the source code.

cpp
Copy code
void choosedifficulty()
{
    // Customize grid size and number of mines based on the chosen difficulty
    // 0: Beginner, 1: Intermediate, 2: Advanced
    int choice;
    std::cin >> choice;
    if (choice == 0)
    {
        SIDE = 9;
        MINES = 10;
    }
    else if (choice == 1)
    {
        SIDE = 16;
        MINES = 40;
    }
    else if (choice == 2)
    {
        SIDE = 24;
        MINES = 99;
    }
    else
        exit(0);
}
Adjust the SIDE and MINES variables according to your preferences.

License
This Minesweeper game is provided under the MIT License.

Feel free to enjoy and modify the game as you like!
