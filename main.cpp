#include <iostream>
#include <windows.h>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include<stdlib.h>
using namespace std;
#define MAX_MINE 99
#define MAX_SIDE 25
#define MAX_MOVE 526 // 25*25-99

int SIDE;
int MINES;

void clearScreen()
{
    system("cls");
}
void ConsoleColor(int textColor, int bgColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor + (bgColor << 4));
}

bool isValidMove(int row, int col)
{
    return (row >= 0) && (row < SIDE) && (col >= 0) && (col < SIDE);
}

bool isMine(int row, int col, char board[][MAX_SIDE])
{
    return (board[row][col] == '*');
}

void makeMove(int *x, int *y)
{
    ConsoleColor(15, 9);

    while (true)
    {
        cout << "\nEnter your move: [row] [column] -> ";
        cin >> *x >> *y;
        if ((*x < SIDE) && (*y < SIDE))
        {
            break;
        }
        cout << "Invalid move. Please try again.\n";
    }

    // Reset text color to default (white on black)
    ConsoleColor(15, 0);
}

void setConsoleColor(int textColor, int bgColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor + (bgColor << 4));
}

void printGameBoard(char myboard[][MAX_SIDE])
{
    clearScreen();

    
    setConsoleColor(15, 9);

    cout << "\n\n\t\t\t    ";
    for (int i = 0; i < SIDE; i++)
    {
        if (i > 9)
            cout << i / 10 << ' ';
        else
            cout << "  ";
    }

    cout << "\n\t\t\t    ";

    for (int i = 0; i < SIDE; i++)
        cout << i % 10 << ' ';

    cout << "\n\n";

    for (int i = 0; i < SIDE; i++)
    {
        cout << "\t\t\t    ";
        for (int j = 0; j < SIDE; j++)
        {
            cout << myboard[i][j] << ' ';
        }
        cout << " " << setw(2) << i << '\n';
    }

    
    setConsoleColor(15, 0);

    return;
}

int countAdjacent(int row, int col, int mines[][2], char realboard[][MAX_SIDE])
{
    int count = 0;

    if (isValidMove(row - 1, col) && isMine(row - 1, col, realboard))
        count++;

    if (isValidMove(row + 1, col) && isMine(row + 1, col, realboard))
        count++;

    if (isValidMove(row, col + 1) && isMine(row, col + 1, realboard))
        count++;

    if (isValidMove(row, col - 1) && isMine(row, col - 1, realboard))
        count++;

    if (isValidMove(row - 1, col - 1) && isMine(row - 1, col - 1, realboard))
        count++;

    if (isValidMove(row - 1, col + 1) && isMine(row - 1, col + 1, realboard))
        count++;

    if (isValidMove(row + 1, col - 1) && isMine(row + 1, col - 1, realboard))
        count++;

    if (isValidMove(row + 1, col + 1) && isMine(row + 1, col + 1, realboard))
        count++;

    return count;
}

bool playMinesUntil(char myboard[][MAX_SIDE], char realboard[][MAX_SIDE], int mines[][2], int row, int col, int *movesLeft)
{
    if (myboard[row][col] != '-')
        return false;

    int i, j;
    if (realboard[row][col] == '*')
    {
        myboard[row][col] = '*';
        for (i = 0; i < MINES; i++)
            myboard[mines[i][0]][mines[i][1]] = '*';

        printGameBoard(myboard);
        // Set text color to white on red background
        setConsoleColor(15, 12);
        cout << "\nYou lost!\n";
        
        setConsoleColor(15, 0);
        return true;
    }
    else
    {
        int count = countAdjacent(row, col, mines, realboard);
        (*movesLeft)--;

        myboard[row][col] = count + '0';

        if (!count)
        {
            if (isValidMove(row - 1, col) && !isMine(row - 1, col, realboard))
                playMinesUntil(myboard, realboard, mines, row - 1, col, movesLeft);

            if (isValidMove(row + 1, col) && !isMine(row + 1, col, realboard))
                playMinesUntil(myboard, realboard, mines, row + 1, col, movesLeft);

            if (isValidMove(row, col + 1) && !isMine(row, col + 1, realboard))
                playMinesUntil(myboard, realboard, mines, row, col + 1, movesLeft);

            if (isValidMove(row, col - 1) && !isMine(row, col - 1, realboard))
                playMinesUntil(myboard, realboard, mines, row, col - 1, movesLeft);

            if (isValidMove(row - 1, col + 1) && !isMine(row - 1, col + 1, realboard))
                playMinesUntil(myboard, realboard, mines, row - 1, col + 1, movesLeft);

            if (isValidMove(row - 1, col - 1) && !isMine(row - 1, col - 1, realboard))
                playMinesUntil(myboard, realboard, mines, row - 1, col - 1, movesLeft);

            if (isValidMove(row + 1, col + 1) && !isMine(row + 1, col + 1, realboard))
                playMinesUntil(myboard, realboard, mines, row + 1, col + 1, movesLeft);

            if (isValidMove(row + 1, col - 1) && !isMine(row + 1, col - 1, realboard))
                playMinesUntil(myboard, realboard, mines, row + 1, col - 1, movesLeft);
        }
        return false;
    }
}

void placeMines(int mines[][2], char realboard[][MAX_SIDE])
{
    bool mark[MAX_SIDE * MAX_SIDE];

    memset(mark, false, sizeof(mark));

    for (int i = 0; i < MINES;)
    {
        int random = rand() % (SIDE * SIDE);
        int x = random / SIDE;
        int y = random % SIDE;

        if (!mark[random])
        {
            mines[i][0] = x;
            mines[i][1] = y;

            realboard[mines[i][0]][mines[i][1]] = '*';
            mark[random] = true;
            i++;
        }
    }
}

void initializeGame(char realboard[][MAX_SIDE], char myboard[][MAX_SIDE])
{
    srand(time(NULL));

    for (int i = 0; i < SIDE; i++)
        for (int j = 0; j < SIDE; j++)
        {
            myboard[i][j] = realboard[i][j] = '-';
        }
}

void cheatMines(char realboard[][MAX_SIDE])
{
    cout << "The mines locations are-\n";
    printGameBoard(realboard);
    return;
}

void replaceMine(int row, int col, char board[][MAX_SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] != '*')
            {
                board[i][j] = '*';
                board[row][col] = '-';
                return;
            }
        }
    }
}

void startGame()
{
    bool gameOver = false;

    char realBoard[MAX_SIDE][MAX_SIDE], playerBoard[MAX_SIDE][MAX_SIDE];

    int movesLeft = SIDE * SIDE - MINES;
    int x, y;
    int mineLocations[MAX_MINE][2];

    initializeGame(realBoard, playerBoard);

    placeMines(mineLocations, realBoard);

    int currentMoveIndex = 0;

    while (!gameOver)
    {
        
        setConsoleColor(15, 9);

        cout << "Current Status of Board:\n";
        printGameBoard(playerBoard);

        
        setConsoleColor(15, 0);

        makeMove(&x, &y);

        if (currentMoveIndex == 0)
        {
            if (isMine(x, y, realBoard))
                replaceMine(x, y, realBoard);
        }

        currentMoveIndex++;

        gameOver = playMinesUntil(playerBoard, realBoard, mineLocations, x, y, &movesLeft);

        if (!gameOver && movesLeft == 0)
        {
            
            setConsoleColor(15, 9);

            cout << "\nYou won!\n";

            
            setConsoleColor(15, 0);

            gameOver = true;
        }
    }
}

void chooseDifficulty()
{
    clearScreen();
    cout << "\n\t\t\t\t\t\t\t\tMINESWEEPER";
    cout << "\n\n\t\t\t\t\t\tCHOOSE DIFFICULTY LEVEL : ";
    cout << "\n\n\t\t\t\t\t\t0.BEGINNER\n\t\t\t\t\t\t1.INTERMEDIATE\n\t\t\t\t\t\t2.ADVANCED";
    cout << "\n\n\t\t\t\t\t\tENTER CHOICE (0-2) : ";
    int choice;
    cin >> choice;
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

int main()
{
    chooseDifficulty();
    startGame();
    return 0;
}
