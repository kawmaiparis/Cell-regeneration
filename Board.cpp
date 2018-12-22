#include <iostream>
#include <algorithm>
#include "Cell.cpp"

using namespace std;

class Board {
  Cell **board;
  int row;
  int col;
  int time;

 public:
  Board(int row, int col) {
    this->row = row;
    this->col = col;
    this->board = new Cell*[row];
    for (int i = 0; i < row; i++)
      board[i] = new Cell[col];
  }

  void seedCells(int cellType, int confluence) {
    cout << "cell type " << cellType << endl;
    int cellsToCreate = row * col * confluence / 100;
    int randomInts[cellsToCreate];
    int *end = randomInts + cellsToCreate;
    int pos = 0;
    srand(1);
    while (pos < cellsToCreate) {
      int newNum = rand() % (row * col);
      if (find(randomInts, end, newNum) == end) {
        randomInts[pos] = newNum;
        pos++;
      }
    }

    int counter = 0;
    int randomSize = sizeof(randomInts) / sizeof(randomInts[0]);

    sort(randomInts, randomInts + cellsToCreate);
    cout << cellType << "type" << endl;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (randomSize > 0 && i * col + j == randomInts[counter]) {
          if (cellType == 1)
            board[i][j] = *new Cell(true);
          else if (cellType == 2) {
            board[i][j] = *new CancerCell(true);
          }
          counter++;
          cout << board[i][j].getToken();
        } else {
          board[i][j] = *new Cell(false);
        }
      }
    }
  }

  void display() {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        cout << board[i][j].getToken();
      }
      cout << endl;
    }
  }

  int getTime() {
    return this->time;
  }

  int getNumCells() {
    int numOfSpace = 0;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (board[i][j].getToken() == '.')
          numOfSpace++;
      }
    }
    return row * col - numOfSpace;
  }

  int getNeighbor(int row, int col) {
    int neighbor = 0;
    int count = 0;
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i != 0 || j != 0) {
          if (row + i >= 0 && col + j >= 0 && row + i < this->row && col + j < this->col
              && board[row + i][col + j].isAlive())
            neighbor++;
        }
      }
    }
    return neighbor;
  }

  void nextState() {
    /* if neighbor <= 1 or neighbor > 4 , kill */
    /* if neighbor = 3 , respawn */
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (board[i][j].isAlive() && (getNeighbor(i, j) >= 4 || getNeighbor(i, j) <= 1)) {
          board[i][j].kill();
        } else if (!board[i][j].isAlive() && getNeighbor(i, j) == 3) {
          board[i][j].respawn();
        }
      }
    }
    this->time++;
  }



};