#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Sudoku {

public:

	void giveQuestion();
	void readIn();
	bool loot1(int row, int col, int n);
	bool loot2(int row, int col, int n);
	bool grid(int cnt);
	void solve();
	void transform();
	void changeNum(int a, int b);
	void changeCol(int a, int b);
	void changeRow(int a, int b);
	void rotate(int n);
	void flip(int n);
	void printfSudokuSolution();

private:

	int j, k, i, n, t, cm, r, bt, ot;
	int  rowT, colT;
	char ch;
	int board[9][9], board2[9][9], board3[9][9], temp[9][9], answer[9][9];
};
