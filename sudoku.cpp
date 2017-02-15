#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
using namespace std;

void printGame(int * input) {
  for(int i = 0; i < 81; i++) {
    if (i > 0) {
      if(i % 3 == 0) {
        cout << " ";
      }
      if(i % 9 == 0) {
        cout << endl;
      }
      if(i % 27 == 0) {
        cout << endl;
      }
    }

    cout << " ";
    if (input[i] == 0) {
      cout << "*";
    } else {
      cout << input[i];
    }
  }
  cout << endl;
}

int select(int _x, int _y, int sqsize) {
  return _x + sqsize * _y;
}

bool verify(int * input, int index) {
  int indexX = index % 9;
  int indexY = index / 9;

  int sqX = indexX / 3;
  int sqY = indexY / 3;
  int sqindex = select(indexX, indexY, 3);
  // Verify the column
  for (int i = 0; i < 9; i++) {
    if (i != indexY) {
      if(input[index] == input[select(indexX, i, 9)]) {
        return false;
      }
    }
  }
  // Verify the line
  for(int i = 0; i < 9; i++) {
    if (i != indexX) {
      if(input[index] == input[select(i, indexY, 9)]) {
          return false;
      }
    }
  }
  // Verify the square
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      int k = 3 * sqX + 27 * sqY + 9 * i + j;
      if(index != k) {
        if(input[index] == input[k]) {
          return false;
        }
      }
    }
  }

  return true;
}

void mknew(int * newgame) {
  for(int i = 0; i < 81;) {
    int in = -1;
    if (i > 0) {
      if(i % 3 == 0) {
        cout << " ";
      }
      if(i % 9 == 0) {
        cout << endl;
      }
      if(i % 27 == 0) {
        cout << endl;
      }
    }

    cout << " ";
    newgame[i] = getch();

    if(newgame[i] >= '0' && newgame[i] <= '9') {
      newgame[i] -= '0';
      if (newgame[i] == 0) {
        cout << "*";
        i++;
      } else {
        if(verify(newgame, i)) {
          cout << newgame[i];
          i++;
        } else {
          cout << '\b';
        }
      }
    } else {
      cout << '\b';
    }
  }
  cout << endl;
}

bool isToComplete(int * ref, int index) {
  return ref[index] == 0;
}

int nextToComplete(int * ref, int start) {
  while(ref[start] != 0 && start < 81) {
    start++;
  }
  return start;
}

int prevToComplete(int * ref, int start) {
  while(ref[start] != 0 && start >= 0) {
    start--;
  }
  return start;
}

bool slvgame(int * solution, int * game) {
  int x;
  int nexti;

  for(int j = 0; j < 81; j++) {
    solution[j] = game[j];
  }

  int i = nextToComplete(game, 0);
  while(i < 81) {
    nexti = i;
    solution[i]++;
    if(solution[i] > 9) {
      solution[i] = 0;
      nexti = prevToComplete(game, i - 1);
    }

    if(verify(solution, i)) {
      nexti = nextToComplete(game, i + 1);
    }
    i = nexti;
  }
  return true;
}

int main() {
  int x;
  system("TITLE Sudoku Solver");
  cout << "*** SUDOKU SOLVER ***" << endl;
  cout << "    by luisbaldissera" << endl;

  int nsolv[81];
  int solv[81];

  for (size_t i = 0; i < 81; i++) {
    nsolv[i] = 0;  // 0 -> Blank
    solv[i] = 0;  // 0 -> Blank
  }

  cout << "\nType the game (use 0 for blank): \n" << endl;
  mknew(nsolv);

  slvgame(solv, nsolv);

  cout << "\n Solved:\n" << endl;
  printGame(solv);

  cout << "\nSee code on GitHub? (Y/N) ";
  char ans = getch();
  cout << ans;
  if(ans == 'Y' or ans == 'y') {
    system("START https://github.com/luisbaldissera/Sudoku-Solver");
  }
  return 0;
}
