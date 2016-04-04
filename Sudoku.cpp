#include "Sudoku.h"

void Sudoku::giveQuestion() {

	cout << "0 4 0 2 1 0 0 0 0" << endl;
	cout << "8 0 7 0 0 0 0 9 0" << endl;
	cout << "2 0 0 8 0 0 4 0 1" << endl;
	cout << "3 0 0 0 0 2 9 0 5" << endl;
	cout << "0 0 5 7 0 8 6 0 0" << endl;
	cout << "7 0 6 5 0 0 0 0 4" << endl;
	cout << "5 0 1 0 0 4 0 0 9" << endl;
	cout << "0 6 0 0 0 0 7 0 8" << endl;
	cout << "0 0 0 0 2 7 0 5 0" << endl;
}

void Sudoku::readIn() {
	bt = 0;

	for (i = 0; i <= 8; i++)
		for (j = 0; j <= 8; j++) {
			cin >> board[i][j];
			temp[i][j] = board[i][j];
			answer[i][j] = board[i][j];
			while (board[i][j] != 0) {
				bt++;
				break;
			}
		}
}

bool Sudoku::loot1(int row, int col, int n) {

	for (i = 0; i<9; i++)
	{
		if ((board[i][col] == n) && (i != row))
			return false;
		if ((board[row][i] == n) && (i != col))
			return false;
	}
	return true;
}

bool Sudoku::loot2(int row, int col, int n) {
	rowT = row / 3;
	colT = col / 3;
	for (i = rowT * 3; i < rowT * 3 + 3; i++)
		for (j = colT * 3; j < colT * 3 + 3; j++)
			if (board[i][j] == n)
				if (i == row&& j == col)
					continue;
				else
					return false;
	return true;
}

bool Sudoku::grid(int cnt) {
	int row, col, n;
	row = cnt / 9;
	col = cnt % 9;
	if (cnt >= 81)
		return true;
	if (board[row][col] == 0)
	{
		for (n = 1; n <= 9; n++)
		{
			board[row][col] = n;
			if (loot1(row, col, n) && loot2(row, col, n))
				if (grid(cnt + 1))
					return true;
			board[row][col] = 0;
		}
	}
	else
		return grid(cnt + 1);

	return false;
}

void Sudoku::solve() {
	
	if (bt == 2) { cout << 0 << endl; exit(1); }
			
	if (bt == 81) goto labe1;
	
	if (grid(0)) {
		for (i = 0; i <= 8; i++)
			for (j = 0; j <= 8; j++) {
				answer[i][j] = board[i][j];
				board[i][j] = temp[i][8 - j];
			}
		grid(0);//1
		for (i = 0; i <= 8; i++)
			for (j = 0; j <= 8; j++) {
				board2[i][j] = board[i][j];
				board[i][j] = temp[8 - i][j];
			}
		grid(0);//2
		for (i = 0; i <= 8; i++)
			for (j = 0; j <= 8; j++) {
				board3[i][j] = board[i][j];
				board[i][j] = temp[8 - i][8 - j];
			}
		grid(0);//3
		for (i = 0; i <= 8; i++)
			for (j = 0; j <= 8; j++) {
				if (board[8 - i][8 - j] != answer[i][j] || board2[i][8 - j] != answer[i][j] || board3[8 - i][j] != answer[i][j]) {
					cout << 2 << endl; exit(1);
				}
			}			
	}
	else  {
		cout << 0 << endl;
		exit(1);
	}
	labe1:
	cout << 1 << endl;
	for (i = 0; i <= 8; i++, cout << endl)
		for (j = 0; j <= 8; j++) {
			cout << answer[i][j] << " ";
		}

}

void Sudoku::transform() {
	
	srand(time(NULL));
	changeNum(rand() % 9 + 1, rand() % 9 + 1);
	changeRow(rand() % 3, rand() % 3);
	changeCol(rand() % 3, rand() % 3);
	rotate(rand() % 101);
	flip(rand() % 2);
	
	printfSudokuSolution();
}

void Sudoku::changeNum(int a, int b) {

	for (i = 0; i <= 8; i++) {
		for (j = 0; j <= 8; j++) {
			temp[i][j] = answer[i][j];
			if (temp[i][j] == a)
				answer[i][j] = b;
			if (temp[i][j] == b)
				answer[i][j] = a;
		}
	}
}

void Sudoku::changeRow(int a, int b) {
	if (a == 1) a = 3; if (b == 1) b = 3;
	if (a == 2) a = 6; if (b == 2) b = 6;
	a = a - 1, b = b - 1;
	for (i = 0; i <= 8; i++)
		for (j = 0; j <= 8; j++)
			temp[i][j] = answer[i][j];
	for (i = 0; i <= 2; i++) {
		a++; b++;
		for (j = 0; j <= 8; j++) {
			answer[a][j] = temp[b][j];
			answer[b][j] = temp[a][j];
		}
	}
}

void Sudoku::changeCol(int a, int b) {

	if (a == 1) a = 3; if (b == 1) b = 3;
	if (a == 2) a = 6; if (b == 2) b = 6;
	a = a - 1, b = b - 1;
	for (i = 0; i <= 8; i++)
		for (j = 0; j <= 8; j++)
			temp[i][j] = answer[i][j];
	for (i = 0; i <= 2; i++) {
		a++, b++;
		for (j = 0; j <= 8; j++) {
			answer[j][a] = temp[j][b];
			answer[j][b] = temp[j][a];
		}
	}
}

void Sudoku::rotate(int n) {

	r = n % 4;

	for (cm = 1; cm <= r; cm++) {
		//粗屎畫二微陣列
		for (i = 0; i <= 8; i++)
			for (j = 0; j <= 8; j++)
				temp[i][j] = answer[i][j];
		for (i = 0, k = 9, t = -1; i <= 8; i++) {
			k--, t++;
			for (j = 0, n = 0; j <= 8; j++) {
				answer[n][k] = temp[t][j];
				n++;
			}
		}
	}
}

void Sudoku::flip(int n) {

	//粗屎畫二微陣列
	for (i = 0; i <= 8; i++)
		for (j = 0; j <= 8; j++)
			temp[i][j] = answer[i][j];
	if (n == 1)
		for (i = 0, k = 9, t = -1; i <= 8; i++) {
			k--, t++;
			if (i == 4)	continue;
			for (j = 0, n = 0; j <= 8; j++) {
				answer[t][n] = temp[k][j];
				n++;
			}
		}
	if (n == 0)
		for (i = 0, k = 9, t = -1; i <= 8; i++) {
			k--, t++;
			if (i == 4)	continue;
			for (j = 0, n = 0; j <= 8; j++) {
				answer[n][t] = temp[j][k];
				n++;
			}
		}
}

void Sudoku::printfSudokuSolution() {
	
	for (i = 0; i <= 8; i++, cout << endl)
		for (j = 0; j <= 8; j++)
			cout << answer[i][j] << " ";
}
