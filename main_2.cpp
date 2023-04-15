/*

MIT License

Copyright (c) 2023 Zaid Shahzad

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 * Objective: Implementation of Conway's Game of Life using two dimensional array. Live cells are denoted as "*". Dead cells are denoted as ".".
 * Developer: Zaid Shahzad
 * Website: https://zaidshahzad.com/

 EX User Input:
    9 18 2
    . * . . . . * . . * . . . * . . * .
    . . . . . . * . . . * * . . . . . *
    . . * . . * . . . * . . . . . . . *
    . * . . . . . . * . . . . . . . . *
    . * * . . . . . . . * . . . . . . .
    . . . . * . . . . * . * * . . . . .
    . . . * * . . . . . * . . . . . . *
    . * * * * . . * . * . * . . . . . *
    . . * . . . * . * * . . . . . . . .
 EX Output (depending on user input):
    . . . . . . . . . * * . . . . . . .
    . . . . . . . . . . . * . . . . * *
    . . . . . . . . * . . . . . . . * *
    . * * . . . . . * . . * . . . . . .
    . * * * . . . . * * . * . . . . . .
    . * * * . . . . . . . * * . . . . .
    . . . * . * * . . * . . . . . . . .
    . * * . * * . * . . . . . . . . . .
    . * * . . . * * . * * . . . . . . .

 */

#include <iostream>
#include <vector>

// This is the Cell Object that is used for the Board
/*
 Properties:
    * isLive
    * posI
    * posJ
 Methods:
    * getDrawnCell() - returns "*" if cell is alive, "." if not (returns string)
    * equals(Cell cell) - checks if current cell object is equal to another cell object (returns bool)
 */
struct Cell {
    bool isLive = false;
    int posI;
    int posJ;

    std::string getDrawnCell() {
        return isLive ? "*" : ".";
    }

    bool equals(Cell cell) {
        return isLive == cell.isLive && posI == cell.posI && posJ == cell.posJ && getDrawnCell() == cell.getDrawnCell();
    }
};

int ROWS;
int COLS;

// This function prints the board
void printBoard(std::vector<std::vector<Cell>> board) {
    for(int i = 0; i < board.size(); i++) {
        std::vector<Cell> row = board[i];
        for(int j = 0; j < row.size(); j++) {
            std::cout << row[j].getDrawnCell();

            // This check makes it so that there is no trailing whitespace at the end of each row.
            if(j != (row.size() - 1)) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

// This function checks if the rows ("I") that is being used in the for loop in the
// "getCellLiveNeighborCount" function is in bounds of the board
bool inBoundsI(int i) {
    if(i < 0 || i >= ROWS) return false;
    return true;
}

// This function checks if the cols ("J") that is being used in the for loop in the
// "getCellLiveNeighborCount" function is in bounds of the board
bool inBoundsJ(int j) {
    if(j < 0 || j >= COLS) return false;
    return true;
}

// This function gets the cell's live nieghbor count (how many cells around it [1 radius] are alive)
int getCellLiveNeighborCount(std::vector<std::vector<Cell>> board, Cell cell) {
    int liveNeighborCount = 0;
    int startingI = cell.posI - 1;
    int startingJ = cell.posJ - 1;

    // This nested for loop loops through the neighbors for the cell
    // that is passed in to the function with a radius of 1
    for(int i = startingI; i <= startingI + 2; i++) {
        // We want to exclude cells that don't exist (rows) (out of bounds)
        if(!inBoundsI(i)) continue;
        for(int j = startingJ; j <= startingJ + 2; j++) {
            // We want to exclude cells that don't exist (cols) (out of bounds)
            if(!inBoundsJ(j)) continue;
            Cell neighbor = board[i][j];
            // We don't want it to do logic on the cell we want it to grab neighbors from
            if(neighbor.equals(cell)) continue;
            if(neighbor.isLive) liveNeighborCount++;
         }
    }
    return liveNeighborCount;
}

// This function returns the updated version of the cell depending on it's live neighbor count following the game rules
/*
  The Rules
    * Any live cell with fewer than two live neighbors dies (as if by underpopulation).
    * Any live cell with more than three live neighbors dies (as if by overpopulation/overcrowding).
    * Any live cell with two or three live neighbors lives, unchanged, to the next generation.
    * Any dead cell with exactly three live neighbors will come to life (as if by reanimation or birth).
 */
Cell getUpdatedCell(std::vector<std::vector<Cell>> board, Cell cell) {
    int liveNieghborCount = getCellLiveNeighborCount(board, cell);

    if(cell.isLive) {
        if(liveNieghborCount < 2) {
            cell.isLive = false;
        }
        else if(liveNieghborCount > 3) {
            cell.isLive = false;
        }
        else {
        }
    }
    else {
        if(liveNieghborCount == 3) {
            cell.isLive = true;
        }
    }
    return cell;
}

// This function applies the ruleset to the oldGenBoard that is passed in to return a newGenBoard which
// contains the new generation cells
std::vector<std::vector<Cell>> applyRulesetToGeneration(std::vector<std::vector<Cell>> oldGenBoard) {
    std::vector<std::vector<Cell>> newGenBoard;
    for (int i = 0; i < oldGenBoard.size(); i++) {
        std::vector<Cell> oldGenRow = oldGenBoard[i];
        std::vector<Cell> newGenRow;
        for (int j = 0; j < oldGenRow.size(); j++) {
            Cell oldGenCell = oldGenRow[j];
            Cell newGenCell = getUpdatedCell(oldGenBoard, oldGenCell);
            newGenRow.push_back(newGenCell);
        }
        newGenBoard.push_back(newGenRow);
    }
    return newGenBoard;
}

int main() {

    // Get inputs from user
    int MAX_GENERATIONS;
    std::cin >> ROWS >> COLS >> MAX_GENERATIONS;

    std::vector<std::vector<Cell>> board;

    std::vector<Cell> cellRowArray;
    std::string input;
    int rowCount = 0;

    // Create the board (0th generation) using the user inputs
    while(std::cin >> input) {
        Cell cell;
        if(input == "*") {
            cell.isLive = true;
        }
        else {
            cell.isLive = false;
        };
        int col = cellRowArray.size();
        cell.posI = rowCount;
        cell.posJ = col;
        cellRowArray.push_back(cell);
        if(col >= (COLS - 1)) {
            board.push_back(cellRowArray);
            cellRowArray.clear();
            rowCount++;
        }
        if(rowCount >= ROWS) break;
    }

    // Print the board "MAX_GENERATION" times for each generation
    for(int i = 1; i <= MAX_GENERATIONS; i++) {
        int currentGeneration = i;
        board = applyRulesetToGeneration(board);
        if(currentGeneration == MAX_GENERATIONS) {
            printBoard(board);
        }
    }
}